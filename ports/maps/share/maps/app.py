import http.server
import socketserver
import urllib.parse
import requests
import json

PORT = 8090

class OpenStreetMapHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        parsed_path = urllib.parse.urlparse(self.path)
        params = dict(urllib.parse.parse_qsl(parsed_path.query))

        if parsed_path.path == '/search':
            if 'q' not in params:
                self.send_error(400, 'Missing search query')
                return

            self.handle_search(params['q'])
        elif parsed_path.path == '/directions':
            if 'from' not in params or 'to' not in params:
                self.send_error(400, 'Missing from or to parameters')
                return

            self.handle_directions(params['from'], params['to'])
        else:
            self.serve_main_page()

    def handle_search(self, query):
        try:
            search_params = {
                'format': 'json',
                'q': query,
                'limit': 5
            }
            url = 'https://nominatim.openstreetmap.org/search'
            headers = {
                'User-Agent': 'BB10OSMApp/1.0'
            }

            response = requests.get(url, params=search_params, headers=headers)
            response.raise_for_status()

            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(response.json()).encode('utf-8'))

        except requests.RequestException as e:
            self.send_error(500, f'Error fetching map data: {e}')

    def handle_directions(self, from_loc, to_loc):
        try:
            # First get coordinates for both locations
            headers = {'User-Agent': 'BB10OSMApp/1.0'}
            
            # Get 'from' coordinates
            from_params = {'format': 'json', 'q': from_loc, 'limit': 1}
            from_response = requests.get('https://nominatim.openstreetmap.org/search', 
                                      params=from_params, headers=headers)
            from_response.raise_for_status()
            from_data = from_response.json()

            # Get 'to' coordinates
            to_params = {'format': 'json', 'q': to_loc, 'limit': 1}
            to_response = requests.get('https://nominatim.openstreetmap.org/search', 
                                    params=to_params, headers=headers)
            to_response.raise_for_status()
            to_data = to_response.json()

            if not from_data or not to_data:
                self.send_error(404, 'Location not found')
                return

            # Get routing data using OSRM
            route_url = f'http://router.project-osrm.org/route/v1/driving/{from_data[0]["lon"]},{from_data[0]["lat"]};{to_data[0]["lon"]},{to_data[0]["lat"]}?overview=full&geometries=geojson'
            route_response = requests.get(route_url)
            route_response.raise_for_status()

            self.send_response(200)
            self.send_header('Content-type', 'application/json')
            self.end_headers()
            self.wfile.write(json.dumps(route_response.json()).encode('utf-8'))

        except requests.RequestException as e:
            self.send_error(500, f'Error fetching directions: {e}')

    def serve_main_page(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()

        html_content = '''
        <!DOCTYPE html>
        <html>
        <head>
            <title>bb10 Maps</title>
            <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css"
                  integrity="sha256-oC6QbFtyOGbNp7G3l1DAuS61n/7N1kGqC2D92iO5iQY="
                  crossorigin=""/>
            <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no, minimal-ui">
            <meta name="apple-mobile-web-app-capable" content="yes">
            <meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
            <meta name="mobile-web-app-capable" content="yes">
            <meta name="theme-color" content="#2b2b2b">
            <style>
                html {
                    height: 100%;
                    width: 100%;
                    overflow: hidden;
                }
                body {
                    background-color: #1e1e1e;
                    color: white;
                    font-family: "Slate Pro", Slate, "Myriad Pro", Helvetica;
                    font-size: 12pt;
                    margin: 0;
                    padding: 0;
                    height: 100%;
                    width: 100%;
                    display: flex;
                    flex-direction: column;
                    overflow: hidden;
                    -webkit-user-select: none;
                    user-select: none;
                    -webkit-tap-highlight-color: rgba(0,0,0,0);
                    position: fixed;
                    top: 0;
                    left: 0;
                    right: 0;
                    bottom: 0;
                }
                .top-bar {
                    background-color: #2b2b2b;
                    border-bottom: 1px solid #3a3a3a;
                    padding: 8px;
                    display: flex;
                    align-items: center;
                    gap: 12px;
                    height: 44px;
                    box-sizing: border-box;
                    position: relative;
                    z-index: 1001;
                }
                .search-container {
                    flex: 1;
                    position: relative;
                    display: flex;
                    gap: 12px;
                }
                .search-input {
                    flex: 1;
                    height: 28px;
                    padding: 0 8px;
                    font-size: 14pt;
                    border: 1px solid #3a3a3a;
                    border-radius: 4px;
                    background-color: #3a3a3a;
                    color: white;
                    -webkit-appearance: none;
                    box-sizing: border-box;
                    outline: none;
                }
                .search-input:focus {
                    border-color: #4a4a4a;
                }
                .menu-button {
                    width: 28px;
                    height: 28px;
                    padding: 0;
                    background: none;
                    border: none;
                    color: white;
                    font-size: 20px;
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    cursor: pointer;
                    margin-left: 12px;
                }
                .icon {
                    font-family: Arial, sans-serif;
                    font-weight: bold;
                    display: inline-block;
                    transform: scale(1.2);
                }
                .menu-overlay {
                    position: fixed;
                    top: 0;
                    left: 0;
                    right: 0;
                    bottom: 0;
                    background: rgba(0,0,0,0.5);
                    z-index: 1000;
                    display: none;
                }
                .side-menu {
                    position: fixed;
                    top: 0;
                    right: -250px;
                    width: 250px;
                    height: 100%;
                    background: #2b2b2b;
                    transition: right 0.3s ease;
                    z-index: 1002;
                    box-shadow: -2px 0 5px rgba(0,0,0,0.3);
                }
                .side-menu.open {
                    right: 0;
                }
                .menu-header {
                    padding: 15px;
                    border-bottom: 1px solid #00769e;
                    font-size: 16pt;
                    color: white;
                }
                .menu-items {
                    list-style: none;
                    margin: 0;
                    padding: 0;
                }
                .menu-item {
                    padding: 12px 15px;
                    border-bottom: 1px solid #3a3a3a;
                    color: white;
                    cursor: pointer;
                }
                .menu-item:active {
                    background-color: #00769e;
                }
                .support-section {
                    position: absolute;
                    bottom: 0;
                    left: 0;
                    right: 0;
                    padding: 15px;
                    background: #232323;
                    border-top: 1px solid #00769e;
                    font-size: 11pt;
                    color: #888;
                    text-align: center;
                }
                .support-link {
                    color: #00769e;
                    text-decoration: none;
                    display: block;
                    margin-top: 4px;
                    font-weight: bold;
                }
                .support-link:active {
                    color: #005b7a;
                }
                #map {
                    flex: 1;
                    width: 100%;
                    height: calc(100% - 44px);
                    border: none;
                    display: block;
                }
                .map-controls {
                    position: absolute;
                    right: 10px;
                    bottom: 120px;
                    z-index: 999;
                    display: flex;
                    flex-direction: column;
                    gap: 5px;
                }
                .map-button {
                    width: 36px;
                    height: 36px;
                    background: white;
                    border: 1px solid #ccc;
                    border-radius: 4px;
                    font-size: 18px;
                    line-height: 36px;
                    text-align: center;
                    cursor: pointer;
                    -webkit-appearance: none;
                    padding: 0;
                    box-shadow: 0 2px 4px rgba(0,0,0,0.2);
                }
                .map-button:active {
                    background: #f0f0f0;
                }
                .location-button {
                    position: absolute;
                    bottom: 80px;
                    right: 10px;
                    z-index: 999;
                    width: 36px;
                    height: 36px;
                    background: white;
                    border: 1px solid #ccc;
                    border-radius: 4px;
                    font-size: 20px;
                    line-height: 36px;
                    text-align: center;
                    box-shadow: 0 2px 4px rgba(0,0,0,0.2);
                    display: flex;
                    align-items: center;
                    justify-content: center;
                    color: #2b2b2b;
                }
                .location-button:active {
                    background: #f0f0f0;
                }
                .error-message {
                    position: absolute;
                    top: 52px;
                    left: 8px;
                    right: 8px;
                    background-color: #ff4444;
                    color: white;
                    padding: 8px;
                    border-radius: 4px;
                    display: none;
                    font-size: 12pt;
                    z-index: 1001;
                }
                .loading-bar {
                    position: absolute;
                    top: 0;
                    left: 0;
                    right: 0;
                    height: 3px;
                    background-color: #00769e;
                    transform: translateX(-100%);
                    display: none;
                    z-index: 1002;
                }
                .loading-bar.active {
                    display: block;
                    animation: loading 2s infinite ease-in-out;
                }
                @keyframes loading {
                    0% { transform: translateX(-100%); }
                    50% { transform: translateX(0); }
                    100% { transform: translateX(100%); }
                }
                .directions-panel {
                    position: absolute;
                    top: 44px;
                    left: 0;
                    right: 0;
                    background: #2b2b2b;
                    padding: 8px;
                    display: none;
                    z-index: 1000;
                    border-bottom: 1px solid #00769e;
                }
                .directions-panel input {
                    width: calc(100% - 16px);
                    height: 28px;
                    padding: 0 8px;
                    font-size: 14pt;
                    border: 1px solid #3a3a3a;
                    border-radius: 4px;
                    background-color: #3a3a3a;
                    color: white;
                    -webkit-appearance: none;
                    box-sizing: border-box;
                    outline: none;
                    margin: 0 0 8px 0;
                }
                .directions-panel input:focus {
                    border-color: #4a4a4a;
                }
                .directions-panel button {
                    width: calc(100% - 16px);
                    height: 28px;
                    padding: 0 8px;
                    font-size: 14pt;
                    border: 1px solid #00769e;
                    border-radius: 4px;
                    background-color: #00769e;
                    color: white;
                    -webkit-appearance: none;
                    box-sizing: border-box;
                    outline: none;
                    cursor: pointer;
                }
                .directions-panel button:active {
                    background-color: #005b7a;
                    border-color: #005b7a;
                }
            </style>
        </head>
        <body>
            <div class="top-bar">
                <div class="search-container">
                    <input type="text" class="search-input" id="searchInput" placeholder="Search location">
                </div>
                <button class="menu-button" onclick="toggleMenu()"><span class="icon">&#9776;</span></button>
                <div class="loading-bar" id="loadingBar"></div>
            </div>

            <div class="menu-overlay" id="menuOverlay" onclick="toggleMenu()"></div>
            <div class="side-menu" id="sideMenu">
                <div class="menu-header">bb10 Maps</div>
                <ul class="menu-items">
                    <li class="menu-item" onclick="handleMenuClick('search')">Search</li>
                    <li class="menu-item" onclick="handleMenuClick('directions')">Directions</li>
                    <li class="menu-item" onclick="handleMenuClick('location')">My Location</li>
                    <li class="menu-item" onclick="handleMenuClick('fullscreen')">Toggle Fullscreen</li>
                </ul>
                <div class="support-section">
                    Support BB10 Development by sw7ft
                    <a href="https://www.patreon.com/c/sw7ft" class="support-link" target="_blank">Become a Patron</a>
                    <a href="https://www.youtube.com/channel/UCip1C0KFjVF58OC906vT1wg" class="support-link" target="_blank">Subscribe on YouTube</a>
                </div>
            </div>

            <div class="directions-panel" id="directionsPanel">
                <input type="text" id="fromInput" placeholder="From location">
                <input type="text" id="toInput" placeholder="To location">
                <button onclick="getDirections()">Get Directions</button>
            </div>

            <div class="error-message" id="errorMessage"></div>
            <div id="map"></div>

            <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"
                    integrity="sha256-o9N1j6tA3GJt6fV6FvXqmC3vF+V5RIjCz5FLeJgqmc8="
                    crossorigin=""></script>
            <script type="text/javascript">
                // Initialize variables
                var map;
                var markersLayer;
                var routeLayer;
                var currentLocationMarker;
                var watchId;
                var currentMode = 'search';

                function initializeMap() {
                    // Create map with zoom control disabled (we'll add our own)
                    map = L.map('map', {
                        zoomControl: false,
                        attributionControl: false
                    });

                    // Add tiles
                    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
                        maxZoom: 19
                    }).addTo(map);

                    // Add layers
                    markersLayer = L.layerGroup().addTo(map);
                    routeLayer = L.layerGroup().addTo(map);

                    // Add custom zoom controls
                    var zoomControls = L.control({position: 'bottomright'});
                    zoomControls.onAdd = function() {
                        var div = L.DomUtil.create('div', 'map-controls');
                        div.innerHTML = 
                            '<button class="map-button" onclick="zoomIn()"><span class="icon">&#x2795;</span></button>' +
                            '<button class="map-button" onclick="zoomOut()"><span class="icon">&#x2796;</span></button>';
                        return div;
                    };
                    zoomControls.addTo(map);

                    // Add location button
                    var locationButton = L.control({position: 'bottomright'});
                    locationButton.onAdd = function() {
                        var div = L.DomUtil.create('div', 'location-button');
                        div.innerHTML = '<span class="icon">&#x1F4CD;</span>';  // Location pin icon
                        div.onclick = centerOnCurrentLocation;
                        return div;
                    };
                    locationButton.addTo(map);

                    // Try to get user's location
                    if (navigator.geolocation) {
                        navigator.geolocation.getCurrentPosition(
                            function(position) {
                                var lat = position.coords.latitude;
                                var lon = position.coords.longitude;
                                map.setView([lat, lon], 15);
                                showCurrentLocation(position);
                            },
                            function(error) {
                                map.setView([45.4215, -75.6972], 13);
                                showError('Could not get your location: ' + getGeolocationErrorMessage(error));
                            },
                            { timeout: 10000, enableHighAccuracy: true }
                        );

                        watchId = navigator.geolocation.watchPosition(
                            showCurrentLocation,
                            function(error) {
                                showError('Location update failed: ' + getGeolocationErrorMessage(error));
                            },
                            { enableHighAccuracy: true }
                        );
                    }

                    // Add search input handler
                    var searchInput = document.getElementById('searchInput');
                    searchInput.onkeypress = function(e) {
                        if (e.keyCode === 13 || e.key === 'Enter') {
                            e.preventDefault();  // Prevent form submission
                            searchLocation();
                        }
                    };

                    // Handle orientation changes
                    window.addEventListener('orientationchange', function() {
                        setTimeout(function() {
                            map.invalidateSize();
                            window.scrollTo(0, 0);
                        }, 200);
                    });

                    // Handle resize events
                    window.addEventListener('resize', function() {
                        map.invalidateSize();
                    });
                }

                function toggleMenu() {
                    var overlay = document.getElementById('menuOverlay');
                    var menu = document.getElementById('sideMenu');
                    var isOpen = menu.className.indexOf('open') !== -1;

                    overlay.style.display = isOpen ? 'none' : 'block';
                    menu.className = isOpen ? 'side-menu' : 'side-menu open';
                }

                function handleMenuClick(action) {
                    toggleMenu();
                    
                    if (action === 'search') {
                        setMode('search');
                    } else if (action === 'directions') {
                        setMode('directions');
                    } else if (action === 'location') {
                        centerOnCurrentLocation();
                    } else if (action === 'fullscreen') {
                        toggleFullscreen();
                    }
                }

                function setMode(mode) {
                    currentMode = mode;
                    var directionsPanel = document.getElementById('directionsPanel');
                    var searchInput = document.getElementById('searchInput');

                    if (mode === 'directions') {
                        directionsPanel.style.display = 'block';
                        searchInput.placeholder = 'Search while navigating';
                    } else {
                        directionsPanel.style.display = 'none';
                        searchInput.placeholder = 'Search location';
                    }

                    clearResults();
                }

                function showCurrentLocation(position) {
                    var lat = position.coords.latitude;
                    var lon = position.coords.longitude;
                    
                    if (!currentLocationMarker) {
                        currentLocationMarker = L.marker([lat, lon]).addTo(map);
                    } else {
                        currentLocationMarker.setLatLng([lat, lon]);
                    }
                }

                function centerOnCurrentLocation() {
                    if (currentLocationMarker) {
                        map.setView(currentLocationMarker.getLatLng(), 15);
                    }
                }

                function clearResults() {
                    if (markersLayer) {
                        markersLayer.clearLayers();
                    }
                    if (routeLayer) {
                        routeLayer.clearLayers();
                    }
                    hideError();
                }

                function showError(message) {
                    var errorDiv = document.getElementById('errorMessage');
                    if (errorDiv) {
                        errorDiv.textContent = message;
                        errorDiv.style.display = 'block';
                        setTimeout(function() {
                            errorDiv.style.display = 'none';
                        }, 5000);
                    }
                }

                function hideError() {
                    document.getElementById('errorMessage').style.display = 'none';
                }

                function getGeolocationErrorMessage(error) {
                    switch(error.code) {
                        case error.PERMISSION_DENIED:
                            return "Location permission denied";
                        case error.POSITION_UNAVAILABLE:
                            return "Location information unavailable";
                        case error.TIMEOUT:
                            return "Location request timed out";
                        default:
                            return "Unknown location error";
                    }
                }

                function searchLocation() {
                    var query = document.getElementById('searchInput').value;
                    if (!query) {
                        showError('Please enter a location to search');
                        return;
                    }

                    clearResults();
                    showLoading();
                    
                    var xhr = new XMLHttpRequest();
                    xhr.open('GET', '/search?q=' + encodeURIComponent(query), true);
                    
                    xhr.onload = function() {
                        hideLoading();
                        if (xhr.status === 200) {
                            try {
                                var results = JSON.parse(xhr.responseText);
                                
                                if (!Array.isArray(results)) {
                                    console.error('Expected array of results, got:', typeof results);
                                    showError('Invalid search results format');
                                    return;
                                }
                                
                                if (results.length === 0) {
                                    showError('No results found');
                                    return;
                                }

                                // Clear existing markers
                                if (markersLayer) {
                                    markersLayer.clearLayers();
                                }

                                var bounds = [];
                                
                                // Add new markers
                                results.forEach(function(r) {
                                    if (r && r.lat && r.lon) {
                                        var lat = parseFloat(r.lat);
                                        var lon = parseFloat(r.lon);
                                        if (!isNaN(lat) && !isNaN(lon)) {
                                            var marker = L.marker([lat, lon]);
                                            marker.bindPopup(r.display_name || 'Location');
                                            markersLayer.addLayer(marker);
                                            bounds.push([lat, lon]);
                                        }
                                    }
                                });

                                // Update map view if we have valid markers
                                if (bounds.length > 0) {
                                    if (bounds.length === 1) {
                                        // Single result - center and zoom
                                        map.setView(bounds[0], 13);
                                    } else {
                                        // Multiple results - fit bounds
                                        map.fitBounds(bounds, {
                                            padding: [50, 50],
                                            maxZoom: 16
                                        });
                                    }
                                }

                                // Handle directions mode
                                if (currentMode === 'directions') {
                                    var fromInput = document.getElementById('fromInput');
                                    var toInput = document.getElementById('toInput');
                                    
                                    if (!fromInput.value) {
                                        fromInput.value = query;
                                    } else if (!toInput.value) {
                                        toInput.value = query;
                                        if (fromInput.value) {
                                            getDirections();
                                        }
                                    }
                                }
                            } catch (e) {
                                console.error('Search error:', e, 'Response:', xhr.responseText);
                                showError('Error processing search results');
                            }
                        } else {
                            console.error('Search failed:', xhr.status, xhr.statusText);
                            showError('Failed to load results');
                        }
                    };
                    
                    xhr.onerror = function(e) {
                        hideLoading();
                        console.error('Search request failed:', e);
                        showError('Error while fetching results');
                    };
                    
                    xhr.send();
                }

                function getDirections() {
                    var from = document.getElementById('fromInput').value;
                    var to = document.getElementById('toInput').value;

                    if (!from || !to) {
                        showError('Please enter both locations');
                        return;
                    }

                    clearResults();
                    document.getElementById('directionsPanel').style.display = 'none';
                    showLoading();

                    var xhr = new XMLHttpRequest();
                    xhr.open('GET', '/directions?from=' + encodeURIComponent(from) + '&to=' + encodeURIComponent(to), true);
                    
                    xhr.onload = function() {
                        hideLoading();
                        if (xhr.status === 200) {
                            var response = JSON.parse(xhr.responseText);
                            
                            if (response.code === 'Ok' && response.routes && response.routes.length > 0) {
                                var route = response.routes[0];
                                var coordinates = route.geometry.coordinates;
                                
                                // Convert coordinates from [lon, lat] to [lat, lon] for Leaflet
                                var latLngs = coordinates.map(function(coord) {
                                    return [coord[1], coord[0]];
                                });

                                // Draw the route
                                var routeLine = L.polyline(latLngs, {
                                    color: '#00769e',
                                    weight: 5,
                                    opacity: 0.8
                                });
                                routeLayer.addLayer(routeLine);

                                // Add markers for start and end
                                var startMarker = L.marker(latLngs[0]).bindPopup('Start');
                                var endMarker = L.marker(latLngs[latLngs.length - 1]).bindPopup('End');
                                markersLayer.addLayer(startMarker);
                                markersLayer.addLayer(endMarker);

                                // Fit map to show the entire route
                                map.fitBounds(routeLine.getBounds().pad(0.1));
                                // Update search input placeholder
                                document.getElementById('searchInput').placeholder = 'Search location';
                            } else {
                                showError('Could not find a route between these locations');
                                // Show directions panel again if route not found
                                document.getElementById('directionsPanel').style.display = 'block';
                            }
                        } else {
                            showError('Failed to get directions');
                            // Show directions panel again if request failed
                            document.getElementById('directionsPanel').style.display = 'block';
                        }
                    };
                    
                    xhr.onerror = function() {
                        hideLoading();
                        showError('Error while fetching directions');
                        // Show directions panel again if request failed
                        document.getElementById('directionsPanel').style.display = 'block';
                    };
                    
                    xhr.send();
                }

                // Add zoom functions
                function zoomIn() {
                    map.setZoom(map.getZoom() + 1);
                }

                function zoomOut() {
                    map.setZoom(map.getZoom() - 1);
                }

                function toggleFullscreen() {
                    if (document.fullscreenElement || 
                        document.webkitFullscreenElement || 
                        document.mozFullScreenElement) {
                        // Exit fullscreen
                        if (document.exitFullscreen) {
                            document.exitFullscreen();
                        } else if (document.webkitExitFullscreen) {
                            document.webkitExitFullscreen();
                        } else if (document.mozCancelFullScreen) {
                            document.mozCancelFullScreen();
                        }
                    } else {
                        // Enter fullscreen
                        if (document.documentElement.requestFullscreen) {
                            document.documentElement.requestFullscreen();
                        } else if (document.documentElement.webkitRequestFullscreen) {
                            document.documentElement.webkitRequestFullscreen();
                        } else if (document.documentElement.mozRequestFullScreen) {
                            document.documentElement.mozRequestFullScreen();
                        }
                    }
                }

                // Initialize map on load
                initializeMap();

                // Handle keyboard events for BB10
                document.addEventListener('keydown', function(e) {
                    if (e.key === 'Escape' || e.keyCode === 27) {
                        // Clear results on BB10 back button
                        clearResults();
                    }
                });

                // Prevent scrolling/bouncing
                document.addEventListener('touchmove', function(e) {
                    e.preventDefault();
                }, { passive: false });

                function showLoading() {
                    document.getElementById('loadingBar').classList.add('active');
                }

                function hideLoading() {
                    document.getElementById('loadingBar').classList.remove('active');
                }
            </script>
        </body>
        </html>
        '''
        self.wfile.write(html_content.encode('utf-8'))

def run_server(port=8090):
    handler = OpenStreetMapHandler
    with socketserver.TCPServer(("", port), handler) as httpd:
        print(f"Serving at port {port}")
        print(f"Open your browser and navigate to http://localhost:{port}")
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\nShutting down the server.")
            httpd.server_close()

if __name__ == "__main__":
    run_server()