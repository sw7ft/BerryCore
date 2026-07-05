/* YouTube Navigator v2.3.3 — ES5 only (BB10 WebKit) */
(function() {
var isSearching = false;
var isStreaming = false;
var currentStreamUrl = '';
var currentQuery = '';
var currentChannel = '';
var currentOffset = 0;
var currentTotal = 0;
var hasMoreResults = false;
var isFullscreen = false;
var STORAGE_QUALITY = 'yt_nav_quality';
var STORAGE_RECENT = 'yt_nav_recent';
var DEFAULT_QUALITY = '360p';
var currentSources = [];
var currentSourceIndex = 0;
var currentStreamMeta = null;
var playbackWatchTimer = null;
var PLAYBACK_TIMEOUT_MS = 10000;
var expandSourcesLoaded = false;
var playbackLocked = false;

function $(id) {
  return document.getElementById(id);
}

function trimStr(value) {
  if (!value) return '';
  return String(value).replace(/^\s+|\s+$/g, '');
}

function hasClass(el, className) {
  if (!el || !el.className) return false;
  return (' ' + el.className + ' ').indexOf(' ' + className + ' ') !== -1;
}

function setText(el, value) {
  if (!el) return;
  if (typeof el.textContent !== 'undefined') {
    el.textContent = value;
  } else {
    el.innerText = value;
  }
}

function escapeHtml(text) {
  if (!text) return '';
  return String(text)
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&#39;');
}

function setStatus(message, type) {
  var el = $('status');
  el.innerHTML = escapeHtml(message);
  el.className = 'status ' + (type || '');
  el.style.display = 'block';
  if (type === 'success') {
    setTimeout(function() {
      el.style.display = 'none';
    }, 3500);
  }
}

function showLoadingOverlay(text) {
  setText($('loadingOverlayText'), text || 'Loading...');
  $('loadingOverlay').style.display = 'block';
}

function hideLoadingOverlay() {
  $('loadingOverlay').style.display = 'none';
}

function clearPlaybackWatch() {
  if (playbackWatchTimer) {
    clearTimeout(playbackWatchTimer);
    playbackWatchTimer = null;
  }
}

function getStoredQuality() {
  try {
    if (window.localStorage) {
      var q = localStorage.getItem(STORAGE_QUALITY);
      if (q) return q;
    }
  } catch (e) {}
  return DEFAULT_QUALITY;
}

function saveQuality(q) {
  try {
    if (window.localStorage) localStorage.setItem(STORAGE_QUALITY, q);
  } catch (e) {}
}

function loadRecent() {
  try {
    if (!window.localStorage) return [];
    var raw = localStorage.getItem(STORAGE_RECENT);
    if (!raw) return [];
    return JSON.parse(raw);
  } catch (e) {
    return [];
  }
}

function saveRecent(query) {
  if (!query) return;
  var list = loadRecent();
  var i, next = [];
  for (i = 0; i < list.length; i++) {
    if (list[i] !== query) next.push(list[i]);
  }
  next.unshift(query);
  if (next.length > 8) {
    next = next.slice(0, 8);
  }
  try {
    if (window.localStorage) localStorage.setItem(STORAGE_RECENT, JSON.stringify(next));
  } catch (e) {}
  renderRecent();
}

function renderRecent() {
  var list = loadRecent();
  var section = $('recentSection');
  var container = $('recentList');
  if (!list.length) {
    section.style.display = 'none';
    return;
  }
  var html = '';
  var i;
  for (i = 0; i < list.length; i++) {
    html += '<span class="chip" data-q="' + escapeHtml(list[i]) + '">' + escapeHtml(list[i]) + '</span>';
  }
  container.innerHTML = html;
  section.style.display = 'block';
  var chips = container.getElementsByClassName('chip');
  for (i = 0; i < chips.length; i++) {
    chips[i].onclick = (function(chip) {
      return function() {
        $('searchInput').value = chip.getAttribute('data-q');
        performSearch(true);
      };
    })(chips[i]);
  }
}

function isYouTubeUrl(text) {
  if (!text) return false;
  return text.indexOf('youtube.com') !== -1 || text.indexOf('youtu.be') !== -1;
}

function normalizeYouTubeUrl(text) {
  var t = trimStr(text);
  if (t.indexOf('http') !== 0) {
    t = 'https://' + t;
  }
  return t;
}

function getVideoIdFromUrl(url) {
  if (!url) return '';
  if (url.indexOf('watch?v=') !== -1) {
    return url.split('watch?v=')[1].split('&')[0];
  }
  if (url.indexOf('youtu.be/') !== -1) {
    return url.split('youtu.be/')[1].split('?')[0];
  }
  if (url.indexOf('/embed/') !== -1) {
    return url.split('/embed/')[1].split('?')[0];
  }
  return '';
}

function getSearchQuery() {
  var query = trimStr($('searchInput').value);
  if (!query && currentQuery) {
    query = currentQuery;
  }
  return query;
}

function resetLoadMoreButton() {
  var btn = $('loadMoreBtn');
  if (!btn) return;
  btn.disabled = false;
  btn.textContent = 'Load More';
}

function performSearch(reset) {
  if (isSearching) return;

  var query = getSearchQuery();
  if (!query) {
    setStatus('Enter a search term or YouTube URL', 'error');
    return;
  }

  if (isYouTubeUrl(query)) {
    streamVideo(normalizeYouTubeUrl(query), 'YouTube video');
    return;
  }

  if (reset !== false) {
    currentOffset = 0;
    currentChannel = '';
    currentQuery = query;
  }

  isSearching = true;
  $('searchButton').disabled = true;
  $('searchButton').innerHTML = '<span class="loading-spinner"></span>';
  setStatus('Searching YouTube...', '');
  $('emptyState').style.display = 'none';

  if (currentOffset === 0) {
    $('results').innerHTML = '<div class="loading"><span class="loading-spinner loading-spinner-large"></span><div>Searching...</div></div>';
  } else {
    var loadBtn = $('loadMoreBtn');
    if (loadBtn) {
      loadBtn.disabled = true;
      loadBtn.textContent = 'Loading...';
    }
  }

  var url = '/api/search?q=' + encodeURIComponent(query) + '&limit=12&offset=' + currentOffset;
  if (currentChannel) {
    url += '&channel=' + encodeURIComponent(currentChannel);
  }

  var xhr = new XMLHttpRequest();
  xhr.open('GET', url, true);
  xhr.timeout = 20000;
  xhr.onreadystatechange = function() {
    if (xhr.readyState !== 4) return;
    isSearching = false;
    $('searchButton').disabled = false;
    $('searchButton').textContent = 'Search';
    resetLoadMoreButton();

    try {
      var res = JSON.parse(xhr.responseText);
      if (xhr.status === 200 && res && res.status === 'ok') {
        currentQuery = res.query;
        currentTotal = res.count;
        hasMoreResults = !!res.has_more;
        currentOffset = res.offset + res.results.length;
        if (reset !== false) saveRecent(res.query);
        displayResults(res.results, res.query, res.count, reset === false);
        var cacheMsg = res.cached ? ' (cached)' : '';
        setStatus('Found ' + res.count + ' videos' + cacheMsg, 'success');
        $('loadMoreSection').style.display = hasMoreResults ? 'block' : 'none';
      } else {
        var err = (res && res.error) ? res.error : ('HTTP ' + xhr.status);
        setStatus('Search failed: ' + err, 'error');
        if (currentOffset === 0) $('results').innerHTML = '';
      }
    } catch (e) {
      setStatus('Error parsing search response', 'error');
      if (currentOffset === 0) $('results').innerHTML = '';
    }
  };
  xhr.ontimeout = function() {
    isSearching = false;
    $('searchButton').disabled = false;
    $('searchButton').textContent = 'Search';
    resetLoadMoreButton();
    setStatus('Search timeout', 'error');
  };
  xhr.onerror = function() {
    isSearching = false;
    $('searchButton').disabled = false;
    $('searchButton').textContent = 'Search';
    resetLoadMoreButton();
    setStatus('Network error', 'error');
  };
  xhr.send();
}

function displayResults(results, query, count, append) {
  var container = $('results');
  var header = $('resultsHeader');

  if (!results || !results.length) {
    if (!append) {
      container.innerHTML = '<div class="empty-state"><h3>No results</h3><p>Try different terms</p></div>';
      header.style.display = 'none';
    }
    return;
  }

  if (!append) {
    header.innerHTML = 'About ' + count + ' results for "' + escapeHtml(query) + '"';
    header.style.display = 'block';
  }

  var html = '';
  var i;
  if (append) {
    var cards = container.getElementsByClassName('video-card');
    for (i = 0; i < cards.length; i++) {
      html += cards[i].outerHTML;
    }
  }

  for (i = 0; i < results.length; i++) {
    var video = results[i];
    var thumbUrl = video.thumbnail ? video.thumbnail.replace('maxresdefault', 'hqdefault').replace('mqdefault', 'hqdefault') : '';
    if (!thumbUrl && video.video_id) {
      thumbUrl = 'https://i.ytimg.com/vi/' + video.video_id + '/hqdefault.jpg';
    }
    html += '<div class="video-card clearfix" data-url="' + escapeHtml(video.url) + '" data-title="' + escapeHtml(video.title) + '">';
    html += '<div class="video-thumbnail">';
    if (thumbUrl) {
      html += '<img src="' + escapeHtml(thumbUrl) + '" alt="">';
    }
    html += '<div class="video-duration">' + escapeHtml(video.duration) + '</div></div>';
    html += '<div class="video-info">';
    html += '<div class="video-title">' + escapeHtml(video.title) + '</div>';
    html += '<div class="video-channel">' + escapeHtml(video.channel) + '</div>';
    html += '<div class="video-meta">' + escapeHtml(video.views) + ' &bull; ' + escapeHtml(video.published) + '</div>';
    html += '</div>';
    html += '<div class="video-actions">';
    html += '<button class="btn btn-primary watch-btn" type="button" data-url="' + escapeHtml(video.url) + '" data-title="' + escapeHtml(video.title) + '">Watch</button>';
    html += '<button class="btn btn-secondary open-btn" type="button" data-url="' + escapeHtml(video.url) + '">Browser</button>';
    html += '</div></div>';
  }

  container.innerHTML = html + '<div class="clearfix"></div>';
  bindResultCards();
}

function bindResultCards() {
  var cards = document.getElementsByClassName('video-card');
  var i;
  for (i = 0; i < cards.length; i++) {
    cards[i].onclick = (function(card) {
      return function(e) {
        var t = e.target || e.srcElement;
        if (t && (hasClass(t, 'open-btn') || hasClass(t, 'btn-secondary'))) {
          return;
        }
        if (t && hasClass(t, 'watch-btn')) return;
        streamVideo(card.getAttribute('data-url'), card.getAttribute('data-title'));
      };
    })(cards[i]);
  }

  var watchBtns = document.getElementsByClassName('watch-btn');
  for (i = 0; i < watchBtns.length; i++) {
    watchBtns[i].onclick = (function(btn) {
      return function(e) {
        if (e.stopPropagation) e.stopPropagation();
        streamVideo(btn.getAttribute('data-url'), btn.getAttribute('data-title'));
      };
    })(watchBtns[i]);
  }

  var openBtns = document.getElementsByClassName('open-btn');
  for (i = 0; i < openBtns.length; i++) {
    openBtns[i].onclick = (function(btn) {
      return function(e) {
        if (e.stopPropagation) e.stopPropagation();
        openYouTube(btn.getAttribute('data-url'));
      };
    })(openBtns[i]);
  }
}

function loadMoreResults() {
  if (!hasMoreResults || isSearching) return;
  performSearch(false);
}

function getCurrentOrigin() {
  return window.location.protocol + '//' + window.location.host;
}

function buildEmbedParams() {
  return 'controls=1&rel=0&modestbranding=1&iv_load_policy=3&fs=1&playsinline=1&enablejsapi=1&origin=' +
    encodeURIComponent(getCurrentOrigin());
}

function buildInstantEmbedUrl(videoId, nocookie, autoplay) {
  var base = nocookie ? 'https://www.youtube-nocookie.com/embed/' : 'https://www.youtube.com/embed/';
  var params = buildEmbedParams();
  if (autoplay) {
    return base + videoId + '?autoplay=1&' + params;
  }
  return base + videoId + '?' + params;
}

function addAutoplayToUrl(url) {
  if (!url || url.indexOf('autoplay=1') !== -1) return url;
  if (url.indexOf('?') === -1) return url + '?autoplay=1';
  return url + '&autoplay=1';
}

function buildInstantSources(videoId) {
  var params = buildEmbedParams();
  var base = 'https://www.youtube.com/embed/' + videoId;
  var nocookie = 'https://www.youtube-nocookie.com/embed/' + videoId;
  return [
    {
      method: 'embed',
      stream_url: base + '?' + params,
      is_embed: true,
      label: 'YouTube embed',
      stream_quality: 'embed',
      stream_type: 'text/html'
    },
    {
      method: 'embed_nocookie',
      stream_url: nocookie + '?' + params,
      is_embed: true,
      label: 'Privacy embed',
      stream_quality: 'embed',
      stream_type: 'text/html'
    },
    {
      method: 'embed_autoplay',
      stream_url: base + '?autoplay=1&' + params,
      is_embed: true,
      label: 'YouTube embed (autoplay)',
      stream_quality: 'embed',
      stream_type: 'text/html'
    }
  ];
}

function showPlayerLoadingHint() {
  var container = $('videoPlayerContainer');
  if (!container) return;
  var hint = $('playerLoadingHint');
  if (!hint) {
    hint = document.createElement('div');
    hint.id = 'playerLoadingHint';
    hint.className = 'player-loading-hint';
    hint.innerHTML = '<span class="loading-spinner"></span> Loading player...';
    container.appendChild(hint);
  }
  hint.style.display = 'block';
}

function hidePlayerLoadingHint() {
  var hint = $('playerLoadingHint');
  if (hint) hint.style.display = 'none';
}

function updateStreamMetadata(res) {
  currentStreamMeta = res;
  if (res.sources && res.sources.length) {
    currentSources = res.sources;
    currentSourceIndex = res.source_index || 0;
  }
  if (res.title) setText($('playerTitle'), res.title);
  if (res.author) {
    var duration = res.length_seconds > 0 ?
      Math.floor(res.length_seconds / 60) + 'm ' + (res.length_seconds % 60) + 's' :
      'Duration unknown';
    setText($('playerMeta'), 'By ' + res.author + ' • ' + duration + ' • ' + (res.stream_quality || 'embed'));
  }
  var badge = $('streamBadge');
  if (badge && res.label) {
    var sourceNum = (res.source_index || 0) + 1;
    var sourceTotal = res.source_count || (res.sources ? res.sources.length : 1);
    setText(badge, res.label + ' (' + sourceNum + '/' + sourceTotal + ')');
    badge.style.display = 'inline-block';
  }
  $('openBrowserBtn').style.display = 'inline-block';
  $('retryStreamBtn').style.display = 'inline-block';
  setText($('retryStreamBtn'), 'Try Next');
}

function showInstantPlayer(url, title) {
  var videoId = getVideoIdFromUrl(url);
  if (!videoId) return false;

  showPlayerSection(title, true);
  showPlayerPoster(url);
  showPlayerLoadingHint();

  currentSources = buildInstantSources(videoId);
  currentSourceIndex = 0;
  currentStreamMeta = {
    title: title,
    author: '',
    length_seconds: 0,
    description: '',
    stream_url: buildInstantEmbedUrl(videoId, false, true),
    is_embed: true,
    method: 'embed',
    label: 'YouTube embed',
    source_index: 0,
    source_count: currentSources.length,
    stream_quality: 'embed'
  };

  renderPlayerSource(currentStreamMeta);
  return true;
}

function fetchStreamMetadata(url, sourceIndex) {
  var quality = $('qualitySelect').value;
  saveQuality(quality);
  var apiUrl = '/api/stream?url=' + encodeURIComponent(url) +
    '&quality=' + encodeURIComponent(quality) +
    '&method=fast&source=' + (sourceIndex || 0);

  var xhr = new XMLHttpRequest();
  xhr.open('GET', apiUrl, true);
  xhr.timeout = 12000;
  xhr.onreadystatechange = function() {
    if (xhr.readyState !== 4) return;
    isStreaming = false;

    try {
      var res = JSON.parse(xhr.responseText);
      if (xhr.status === 200 && res && res.status === 'ok') {
        var sameVideo = getVideoIdFromUrl(url) === getVideoIdFromUrl(currentStreamUrl);
        var iframe = $('videoPlayerContainer').getElementsByTagName('iframe')[0];
        if (sameVideo && iframe && iframe.src) {
          updateStreamMetadata(res);
        } else {
          currentStreamMeta = res;
          currentSources = res.sources || currentSources;
          currentSourceIndex = res.source_index || 0;
          renderPlayerSource(res);
        }
        setStatus('Now playing: ' + res.title, 'success');
        prefetchExpandSources(url, quality);
      } else if (getVideoIdFromUrl(url) === getVideoIdFromUrl(currentStreamUrl)) {
        $('retryStreamBtn').style.display = 'inline-block';
        $('openBrowserBtn').style.display = 'inline-block';
      }
    } catch (e) {
      if (getVideoIdFromUrl(url) === getVideoIdFromUrl(currentStreamUrl)) {
        $('retryStreamBtn').style.display = 'inline-block';
        $('openBrowserBtn').style.display = 'inline-block';
      }
    }
  };
  xhr.ontimeout = function() {
    isStreaming = false;
    if (getVideoIdFromUrl(url) === getVideoIdFromUrl(currentStreamUrl)) {
      $('retryStreamBtn').style.display = 'inline-block';
      $('openBrowserBtn').style.display = 'inline-block';
    }
  };
  xhr.onerror = function() {
    isStreaming = false;
  };
  xhr.send();
}

function showPlayerPoster(url) {
  var poster = $('playerPoster');
  var videoId = getVideoIdFromUrl(url);
  if (!poster || !videoId) return;
  poster.src = 'https://i.ytimg.com/vi/' + videoId + '/hqdefault.jpg';
  poster.style.display = 'block';
}

function hidePlayerPoster() {
  var poster = $('playerPoster');
  if (poster) poster.style.display = 'none';
}

function prefetchExpandSources(url, quality) {
  if (expandSourcesLoaded) return;
  var xhr = new XMLHttpRequest();
  xhr.open('GET', '/api/stream?url=' + encodeURIComponent(url) +
    '&quality=' + encodeURIComponent(quality) + '&method=expand', true);
  xhr.timeout = 45000;
  xhr.onreadystatechange = function() {
    if (xhr.readyState !== 4) return;
    expandSourcesLoaded = true;
    try {
      var res = JSON.parse(xhr.responseText);
      if (xhr.status === 200 && res && res.status === 'ok' && res.sources && res.sources.length) {
        var i, seen = {};
        for (i = 0; i < currentSources.length; i++) {
          seen[currentSources[i].method] = true;
        }
        for (i = 0; i < res.sources.length; i++) {
          if (!seen[res.sources[i].method]) {
            currentSources.push(res.sources[i]);
            seen[res.sources[i].method] = true;
          }
        }
        if (currentStreamMeta && res.title && currentStreamMeta.title === 'YouTube Video') {
          currentStreamMeta.title = res.title;
          setText($('playerTitle'), res.title);
        }
        if (res.author) {
          var meta = $('playerMeta');
          if (meta && meta.textContent && meta.textContent.indexOf('By ') === 0) {
            setText(meta, 'By ' + res.author);
          }
        }
      }
    } catch (e) {}
  };
  xhr.send();
}

function streamVideo(url, title, sourceIndex) {
  var isAltSource = (sourceIndex !== undefined && sourceIndex !== null && sourceIndex > 0);
  var isQualityRetry = (sourceIndex === 0 && playbackLocked && url === currentStreamUrl);

  if (isAltSource || isQualityRetry) {
    isStreaming = true;
    currentStreamUrl = url;
    expandSourcesLoaded = false;
    playbackLocked = false;
    currentSourceIndex = sourceIndex || 0;
    clearPlaybackWatch();
    showPlayerSection(title, false);
    fetchStreamMetadataAndRender(url, sourceIndex || 0, title);
    return;
  }

  currentStreamUrl = url;
  expandSourcesLoaded = false;
  playbackLocked = false;
  currentSourceIndex = 0;
  clearPlaybackWatch();
  isStreaming = true;

  if (showInstantPlayer(url, title)) {
    setStatus('Loading: ' + title, '');
    fetchStreamMetadata(url, 0);
    return;
  }

  showPlayerSection(title, false);
  showPlayerPoster(url);
  fetchStreamMetadataAndRender(url, 0, title);
}

function fetchStreamMetadataAndRender(url, sourceIndex, title) {
  var quality = $('qualitySelect').value;
  saveQuality(quality);
  var apiUrl = '/api/stream?url=' + encodeURIComponent(url) +
    '&quality=' + encodeURIComponent(quality) +
    '&method=fast&source=' + (sourceIndex || 0);

  var xhr = new XMLHttpRequest();
  xhr.open('GET', apiUrl, true);
  xhr.timeout = 12000;
  xhr.onreadystatechange = function() {
    if (xhr.readyState !== 4) return;
    isStreaming = false;

    try {
      var res = JSON.parse(xhr.responseText);
      if (xhr.status === 200 && res && res.status === 'ok') {
        currentStreamMeta = res;
        currentSources = res.sources || [];
        currentSourceIndex = res.source_index || 0;
        showPlayer(res);
        setStatus('Now playing: ' + res.title, 'success');
        prefetchExpandSources(url, quality);
      } else {
        var err = (res && res.error) ? res.error : ('HTTP ' + xhr.status);
        setStatus('Stream failed: ' + err, 'error');
        $('retryStreamBtn').style.display = 'inline-block';
        $('openBrowserBtn').style.display = 'inline-block';
      }
    } catch (e) {
      setStatus('Error loading stream', 'error');
      $('retryStreamBtn').style.display = 'inline-block';
      $('openBrowserBtn').style.display = 'inline-block';
    }
  };
  xhr.ontimeout = function() {
    isStreaming = false;
    $('retryStreamBtn').style.display = 'inline-block';
    $('openBrowserBtn').style.display = 'inline-block';
    setStatus('Stream timeout', 'error');
  };
  xhr.onerror = function() {
    isStreaming = false;
    $('retryStreamBtn').style.display = 'inline-block';
    $('openBrowserBtn').style.display = 'inline-block';
    setStatus('Stream network error', 'error');
  };
  xhr.send();
}

function scrollToElementIfNeeded(el) {
  if (!el) return;
  var top = 0;
  var node = el;
  while (node) {
    top += node.offsetTop || 0;
    node = node.offsetParent;
  }
  var scrollY = window.pageYOffset || document.documentElement.scrollTop || document.body.scrollTop || 0;
  var viewH = window.innerHeight || document.documentElement.clientHeight || 480;
  if (top > scrollY + (viewH * 0.35)) {
    if (window.scrollTo) {
      window.scrollTo(0, top);
    }
  }
}

function showPlayerSection(title, instant) {
  var section = $('playerSection');
  section.style.display = 'block';
  setText($('playerTitle'), title);
  setText($('playerMeta'), instant ? 'Starting player...' : 'Loading...');
  setText($('playerDescription'), '');
  $('streamBadge').style.display = 'none';
  $('openBrowserBtn').style.display = 'none';
  $('retryStreamBtn').style.display = 'none';
  if (!instant) {
    scrollToElementIfNeeded(section);
  }
}

function removeTapOverlay() {
  var existing = $('tapToPlayOverlay');
  if (existing && existing.parentNode) {
    existing.parentNode.removeChild(existing);
  }
}

function markPlaybackActive() {
  playbackLocked = true;
  clearPlaybackWatch();
}

function schedulePlaybackWatch(isEmbed) {
  clearPlaybackWatch();
  if (isEmbed) {
    return;
  }
  playbackWatchTimer = setTimeout(function() {
    playbackWatchTimer = null;
    if (!playbackLocked) {
      tryNextSource('timeout');
    }
  }, PLAYBACK_TIMEOUT_MS);
}

function tryNextSource(reason) {
  if (playbackLocked && reason === 'timeout') {
    return;
  }
  if (!currentSources || !currentSources.length) {
    $('retryStreamBtn').style.display = 'inline-block';
    $('openBrowserBtn').style.display = 'inline-block';
    setStatus('Playback failed — tap Retry or Open in Browser', 'error');
    return;
  }

  var nextIndex = currentSourceIndex + 1;
  if (nextIndex >= currentSources.length) {
    $('retryStreamBtn').style.display = 'inline-block';
    $('openBrowserBtn').style.display = 'inline-block';
    setStatus('All playback methods tried — use Browser or Retry', 'error');
    return;
  }

  var nextSource = currentSources[nextIndex];
  setStatus('Switching to ' + (nextSource.label || nextSource.method) + '...', '');
  playSourceAtIndex(nextIndex, currentStreamMeta);
}

function playSourceAtIndex(index, meta) {
  if (!currentSources || index < 0 || index >= currentSources.length) return;

  clearPlaybackWatch();
  removeTapOverlay();
  currentSourceIndex = index;

  var source = currentSources[index];
  var streamData = {
    title: meta.title,
    author: meta.author,
    length_seconds: meta.length_seconds,
    description: meta.description,
    stream_url: source.stream_url,
    stream_quality: source.stream_quality,
    stream_type: source.stream_type,
    is_embed: source.is_embed,
    method: source.method,
    label: source.label,
    source_index: index,
    source_count: currentSources.length
  };

  renderPlayerSource(streamData);
}

function renderPlayerSource(streamData) {
  var playerContainer = $('videoPlayerContainer');
  var badge = $('streamBadge');
  var existingPoster = $('playerPoster');
  var posterSrc = existingPoster ? existingPoster.src : '';
  playerContainer.innerHTML = '';

  if (posterSrc) {
    var poster = document.createElement('img');
    poster.id = 'playerPoster';
    poster.className = 'player-poster';
    poster.src = posterSrc;
    poster.alt = '';
    playerContainer.appendChild(poster);
  }

  var sourceLabel = streamData.label || streamData.method || 'unknown';
  var sourceNum = (streamData.source_index || 0) + 1;
  var sourceTotal = streamData.source_count || currentSources.length || 1;

  if (streamData.is_embed) {
    badge.className = 'stream-badge embed';
    setText(badge, sourceLabel + ' (' + sourceNum + '/' + sourceTotal + ')');
    badge.style.display = 'inline-block';
    $('openBrowserBtn').style.display = 'inline-block';
    $('retryStreamBtn').style.display = 'inline-block';
    setText($('retryStreamBtn'), 'Try Next');

    var embedUrl = addAutoplayToUrl(streamData.stream_url);
    var iframe = document.createElement('iframe');
    iframe.src = embedUrl;
    iframe.setAttribute('frameborder', '0');
    iframe.setAttribute('allowfullscreen', 'true');
    iframe.setAttribute('title', streamData.title || 'YouTube');
    iframe.onload = function() {
      hidePlayerPoster();
      hidePlayerLoadingHint();
      markPlaybackActive();
    };
    playerContainer.appendChild(iframe);
    showPlayerLoadingHint();
  } else {
    badge.className = 'stream-badge direct';
    setText(badge, sourceLabel + ' (' + sourceNum + '/' + sourceTotal + ')');
    badge.style.display = 'inline-block';
    $('retryStreamBtn').style.display = 'inline-block';
    setText($('retryStreamBtn'), 'Try Next');
    $('openBrowserBtn').style.display = 'inline-block';

    var video = document.createElement('video');
    video.src = streamData.stream_url;
    video.setAttribute('controls', 'true');
    video.id = 'videoPlayer';
    video.onerror = function() {
      setStatus('Direct play failed — trying next source...', 'error');
      tryNextSource('video_error');
    };
    video.oncanplay = function() {
      markPlaybackActive();
      hidePlayerPoster();
    };
    playerContainer.appendChild(video);
    schedulePlaybackWatch(false);
  }

  setText($('playerTitle'), streamData.title);
  var duration = streamData.length_seconds > 0 ?
    Math.floor(streamData.length_seconds / 60) + 'm ' + (streamData.length_seconds % 60) + 's' :
    'Duration unknown';
  setText($('playerMeta'), 'By ' + streamData.author + ' • ' + duration + ' • ' + streamData.stream_quality);
  setText($('playerDescription'), streamData.description || '');
  $('playerSection').style.display = 'block';
}

function showPlayer(streamData) {
  if (streamData.sources && streamData.sources.length) {
    currentSources = streamData.sources;
    currentSourceIndex = streamData.source_index || 0;
  }
  var iframe = $('videoPlayerContainer').getElementsByTagName('iframe')[0];
  var vid = getVideoIdFromUrl(currentStreamUrl);
  if (iframe && streamData.is_embed && vid && iframe.src.indexOf(vid) !== -1) {
    updateStreamMetadata(streamData);
    return;
  }
  renderPlayerSource(streamData);
}

function changeQuality() {
  saveQuality($('qualitySelect').value);
  if (currentStreamUrl) {
    streamVideo(currentStreamUrl, $('playerTitle').textContent || $('playerTitle').innerText || 'Video', 0);
  }
}

function retryStream() {
  $('retryStreamBtn').style.display = 'none';
  if (currentSources && currentSourceIndex < currentSources.length - 1) {
    tryNextSource('manual');
    return;
  }
  if (currentStreamUrl) {
    streamVideo(currentStreamUrl, $('playerTitle').textContent || $('playerTitle').innerText || 'Video', 0);
  }
}

function closePlayer() {
  clearPlaybackWatch();
  removeTapOverlay();
  hidePlayerPoster();
  hidePlayerLoadingHint();
  expandSourcesLoaded = false;
  playbackLocked = false;
  if (isFullscreen) exitFullscreen();
  var playerContainer = $('videoPlayerContainer');
  var video = playerContainer.getElementsByTagName('video')[0];
  var iframe = playerContainer.getElementsByTagName('iframe')[0];
  if (video && video.pause) { video.pause(); video.src = ''; }
  if (iframe) { iframe.src = ''; }
  playerContainer.innerHTML = '<video id="videoPlayer" controls>Your browser does not support video.</video>';
  $('playerSection').style.display = 'none';
  currentStreamUrl = '';
  currentSources = [];
  currentSourceIndex = 0;
  currentStreamMeta = null;
  $('streamBadge').style.display = 'none';
  setText($('retryStreamBtn'), 'Retry');
  setStatus('Player closed', 'success');
}

function openYouTube(url) {
  if (url) window.open(url, '_blank');
}

function toggleFullscreen() {
  if (isFullscreen) exitFullscreen();
  else enterFullscreen();
}

function enterFullscreen() {
  var playerContainer = $('videoPlayerContainer');
  if (!playerContainer.getElementsByTagName('iframe')[0] && !playerContainer.getElementsByTagName('video')[0]) {
    setStatus('No video playing', 'error');
    return;
  }
  $('fullscreenOverlay').style.display = 'block';
  $('fullscreenControls').style.display = 'block';
  playerContainer.className = 'video-player fullscreen-player';
  document.body.style.overflow = 'hidden';
  isFullscreen = true;
}

function exitFullscreen() {
  $('fullscreenOverlay').style.display = 'none';
  $('fullscreenControls').style.display = 'none';
  $('videoPlayerContainer').className = 'video-player';
  document.body.style.overflow = 'auto';
  isFullscreen = false;
}

function initApp() {
  var q = getStoredQuality();
  $('qualitySelect').value = q;
  renderRecent();

  $('searchButton').onclick = function() { performSearch(true); };
  $('loadMoreBtn').onclick = loadMoreResults;
  $('closePlayerBtn').onclick = closePlayer;
  $('fullscreenBtn').onclick = toggleFullscreen;
  $('exitFullscreenBtn').onclick = exitFullscreen;
  $('retryStreamBtn').onclick = retryStream;
  $('qualitySelect').onchange = changeQuality;
  $('openBrowserBtn').onclick = function() {
    if (currentStreamUrl) openYouTube(currentStreamUrl);
  };

  var searchForm = $('searchForm');
  if (searchForm) {
    searchForm.onsubmit = function() {
      performSearch(true);
      return false;
    };
  }

  $('searchInput').onkeypress = function(e) {
    var code = e.keyCode || e.which;
    if (code === 13) {
      performSearch(true);
      return false;
    }
  };

  $('searchInput').focus();
}

if (document.addEventListener) {
  document.addEventListener('DOMContentLoaded', initApp, false);
} else if (document.attachEvent) {
  document.attachEvent('onreadystatechange', function() {
    if (document.readyState === 'complete') initApp();
  });
} else {
  window.onload = initApp;
}

})();
