/* RocketChat Navigator v3 — ES5 client for BB10 WebKit */
(function() {
    var selectedChatId = null;
    var selectedChatName = '';
    var currentFilter = 'all';
    var roomsData = { channels: [], groups: [], direct_messages: [] };
    var pollTimer = null;
    var msgCount = 40;
    var sidebarOpen = false;
    var loadingRoomId = null;
    var msgLoading = false;
    var unreadMap = {};
    var unreadTotal = 0;
    var lastAlertTime = 0;
    var currentAlert = null;

    function $(id) { return document.getElementById(id); }

    function dismissCurrentAlert() {
        var bar = $('notify-bar');
        if (bar) bar.style.display = 'none';
        var payload = { alert_id: '', room_id: '', time: 0 };
        if (currentAlert) {
            payload.alert_id = currentAlert.id || '';
            payload.room_id = currentAlert.room_id || '';
            payload.time = currentAlert.time || 0;
        } else if (lastAlertTime) {
            payload.time = lastAlertTime;
        }
        xhr('POST', '/api/dismiss_alert', JSON.stringify(payload), null);
        currentAlert = null;
    }

    function showMsgLoading(text) {
        var el = $('msg-loading');
        if (!el) return;
        var label = el.getElementsByTagName('p')[0];
        if (label) label.textContent = text || 'Loading messages...';
        el.className = 'msg-loading show';
        msgLoading = true;
    }

    function hideMsgLoading() {
        var el = $('msg-loading');
        if (!el) return;
        el.className = 'msg-loading';
        msgLoading = false;
    }

    function xhr(method, url, body, cb) {
        var req = new XMLHttpRequest();
        req.open(method, url, true);
        if (body) {
            req.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
        }
        req.onreadystatechange = function() {
            if (req.readyState === 4) {
                var data = null;
                try { data = JSON.parse(req.responseText); } catch (e) {}
                cb(req.status, data, req.responseText);
            }
        };
        req.send(body || null);
    }

    function escapeHtml(text) {
        if (!text) return '';
        return String(text)
            .replace(/&/g, '&amp;')
            .replace(/</g, '&lt;')
            .replace(/>/g, '&gt;')
            .replace(/"/g, '&quot;');
    }

    function linkify(text) {
        var safe = escapeHtml(text);
        var parts = safe.split(/(https?:\/\/[^\s<]+)/g);
        var out = '';
        for (var i = 0; i < parts.length; i++) {
            if (parts[i].indexOf('http://') === 0 || parts[i].indexOf('https://') === 0) {
                out += '<a href="' + parts[i] + '" target="_blank" rel="noopener">' + parts[i] + '</a>';
            } else {
                out += parts[i];
            }
        }
        return out.replace(/\n/g, '<br>');
    }

    function formatDisplayTime(dateStr) {
        if (!dateStr) return '';
        try {
            var d = new Date(dateStr.replace(' ', 'T'));
            if (isNaN(d.getTime())) return dateStr;
            var h = d.getHours() % 12 || 12;
            var m = d.getMinutes();
            var ampm = d.getHours() >= 12 ? 'PM' : 'AM';
            return h + ':' + (m < 10 ? '0' : '') + m + ' ' + ampm;
        } catch (e) {
            return dateStr;
        }
    }

    function setSidebar(open) {
        sidebarOpen = open;
        var sb = $('sidebar');
        var ov = $('overlay');
        if (open) {
            sb.className = 'sidebar open';
            ov.className = 'overlay show';
            document.body.style.overflow = 'hidden';
        } else {
            sb.className = 'sidebar';
            ov.className = 'overlay';
            document.body.style.overflow = '';
        }
    }

    function toggleSidebar() {
        setSidebar(!sidebarOpen);
    }

    function closeSidebarMobile() {
        if (window.innerWidth < 769) {
            setSidebar(false);
        }
    }

    function markRoomActive(chatId, messageId) {
        xhr('POST', '/api/active_room', JSON.stringify({ chat_id: chatId || '' }), null);
        if (chatId) {
            xhr('POST', '/api/mark_read', JSON.stringify({
                chat_id: chatId,
                message_id: messageId || ''
            }), null);
            unreadMap[chatId] = 0;
            updateUnreadUI();
        }
    }

    function updateUnreadUI() {
        var badge = $('unread-badge');
        var total = 0;
        var rid;
        for (rid in unreadMap) {
            if (unreadMap.hasOwnProperty(rid) && unreadMap[rid] > 0) {
                total += unreadMap[rid];
            }
        }
        unreadTotal = total;
        if (roomsData && typeof roomsData.unread_total === 'number') {
            unreadTotal = roomsData.unread_total;
        }
        if (badge) {
            if (unreadTotal > 0) {
                badge.style.display = 'inline-block';
                badge.textContent = unreadTotal > 99 ? '99+' : String(unreadTotal);
            } else {
                badge.style.display = 'none';
            }
        }
    }

    function showInAppAlert(alert) {
        if (!alert || !alert.time) {
            $('notify-bar').style.display = 'none';
            currentAlert = null;
            return;
        }
        if (alert.room_id === selectedChatId) {
            dismissCurrentAlert();
            return;
        }
        var bar = $('notify-bar');
        var text = $('notify-text');
        if (!bar || !text) return;
        text.innerHTML = '<strong>' + escapeHtml(alert.room) + '</strong> ' +
            escapeHtml(alert.from) + ': ' + escapeHtml(alert.text);
        bar.style.display = 'flex';
        lastAlertTime = alert.time;
        currentAlert = alert;
    }

    function pollUnread() {
        xhr('GET', '/api/unread', null, function(status, data) {
            if (status !== 200 || !data) return;
            if (data.unread) unreadMap = data.unread;
            unreadTotal = data.unread_total || 0;
            updateUnreadUI();
            if (data.alert) {
                showInAppAlert(data.alert);
            } else {
                $('notify-bar').style.display = 'none';
                currentAlert = null;
            }
            renderRooms();
        });
    }

    function mergeUnreadFromRooms() {
        var lists = [roomsData.channels, roomsData.groups, roomsData.direct_messages];
        var i, j, room;
        for (i = 0; i < lists.length; i++) {
            if (!lists[i]) continue;
            for (j = 0; j < lists[i].length; j++) {
                room = lists[i][j];
                if (room && room.id) {
                    unreadMap[room.id] = room.unread || 0;
                }
            }
        }
        if (typeof roomsData.unread_total === 'number') {
            unreadTotal = roomsData.unread_total;
        }
        updateUnreadUI();
    }

    function updateStatus() {
        xhr('GET', '/api/status', null, function(status, data) {
            var dot = $('status-dot');
            var text = $('status-text');
            var user = $('status-user');
            if (status === 200 && data && data.connected) {
                dot.className = 'status-dot ok';
                text.textContent = 'Connected';
                user.textContent = '@' + (data.user || '');
            } else {
                dot.className = 'status-dot err';
                text.textContent = (data && data.message) ? data.message : 'Offline';
                user.textContent = '';
            }
        });
    }

    function allRoomsList() {
        var list = [];
        var i;
        for (i = 0; i < roomsData.channels.length; i++) list.push(roomsData.channels[i]);
        for (i = 0; i < roomsData.groups.length; i++) list.push(roomsData.groups[i]);
        for (i = 0; i < roomsData.direct_messages.length; i++) list.push(roomsData.direct_messages[i]);
        return list;
    }

    function filteredRooms() {
        if (currentFilter === 'channel') return roomsData.channels || [];
        if (currentFilter === 'group') return roomsData.groups || [];
        if (currentFilter === 'dm') return roomsData.direct_messages || [];
        return allRoomsList();
    }

    function renderRooms() {
        var container = $('rooms');
        var search = ($('search-input').value || '').toLowerCase();
        var rooms = filteredRooms();
        var html = '';
        var i, room, name, preview;

        if (currentFilter === 'all') {
            if (roomsData.channels && roomsData.channels.length) {
                html += '<div class="section-label">Channels</div>';
                for (i = 0; i < roomsData.channels.length; i++) {
                    room = roomsData.channels[i];
                    name = (room.display || room.name || '').toLowerCase();
                    preview = (room.preview || '').toLowerCase();
                    if (search && name.indexOf(search) === -1 && preview.indexOf(search) === -1) continue;
                    html += roomButtonHtml(room);
                }
            }
            if (roomsData.groups && roomsData.groups.length) {
                html += '<div class="section-label">Private groups</div>';
                for (i = 0; i < roomsData.groups.length; i++) {
                    room = roomsData.groups[i];
                    name = (room.display || room.name || '').toLowerCase();
                    preview = (room.preview || '').toLowerCase();
                    if (search && name.indexOf(search) === -1 && preview.indexOf(search) === -1) continue;
                    html += roomButtonHtml(room);
                }
            }
            if (roomsData.direct_messages && roomsData.direct_messages.length) {
                html += '<div class="section-label">Direct messages</div>';
                for (i = 0; i < roomsData.direct_messages.length; i++) {
                    room = roomsData.direct_messages[i];
                    name = (room.display || room.name || '').toLowerCase();
                    preview = (room.preview || '').toLowerCase();
                    if (search && name.indexOf(search) === -1 && preview.indexOf(search) === -1) continue;
                    html += roomButtonHtml(room);
                }
            }
        } else {
            for (i = 0; i < rooms.length; i++) {
                room = rooms[i];
                name = (room.display || room.name || '').toLowerCase();
                preview = (room.preview || '').toLowerCase();
                if (search && name.indexOf(search) === -1 && preview.indexOf(search) === -1) continue;
                html += roomButtonHtml(room);
            }
        }

        if (!html) {
            html = '<div class="empty-state">No rooms found</div>';
        }
        container.innerHTML = html;

        var buttons = container.querySelectorAll('.room-item');
        for (i = 0; i < buttons.length; i++) {
            buttons[i].onclick = onRoomClick;
        }
    }

    function roomButtonHtml(room) {
        var active = room.id === selectedChatId ? ' active' : '';
        var loading = room.id === loadingRoomId ? ' loading' : '';
        var unread = room.unread || unreadMap[room.id] || 0;
        var hasUnread = unread > 0 ? ' has-unread' : '';
        var preview = room.preview ? escapeHtml(room.preview) : '&nbsp;';
        var time = room.time ? escapeHtml(room.time) : '';
        var spinner = room.id === loadingRoomId ? '<span class="room-spinner"></span>' : '';
        var unreadBadge = unread > 0 ? '<span class="room-unread">' + (unread > 9 ? '9+' : String(unread)) + '</span>' : '';
        return '<button type="button" class="room-item' + active + loading + hasUnread + '" data-id="' + escapeHtml(room.id) + '" data-name="' + escapeHtml(room.display || room.name) + '">' +
            '<div class="room-row"><span class="room-name">' + escapeHtml(room.display || room.name) + spinner + unreadBadge + '</span>' +
            '<span class="room-time">' + time + '</span></div>' +
            '<div class="room-preview">' + preview + '</div></button>';
    }

    function onRoomClick(e) {
        var btn = e.currentTarget || e.target;
        while (btn && !btn.getAttribute('data-id')) btn = btn.parentNode;
        if (!btn) return;
        selectRoom(btn.getAttribute('data-id'), btn.getAttribute('data-name'));
    }

    function selectRoom(id, name) {
        selectedChatId = id;
        selectedChatName = name;
        loadingRoomId = id;
        $('chat-title').textContent = name;
        $('chat-header').className = 'chat-header show';
        var empty = $('empty-chat');
        if (empty) empty.style.display = 'none';
        showMsgLoading('Loading messages...');
        markRoomActive(id, '');
        renderRooms();
        closeSidebarMobile();
        fetchMessages(id, false);
        startPolling();
    }

    function renderMessages(messages, prepend) {
        var box = $('messages');
        var html = '';
        var lastDay = '';
        var i, msg, day;

        if (!prepend) {
            html += '<button type="button" class="load-more" id="load-more-btn">Load older messages</button>';
        }

        for (i = messages.length - 1; i >= 0; i--) {
            msg = messages[i];
            day = msg.day || '';
            if (day && day !== lastDay) {
                html += '<div class="day-divider"><span>' + escapeHtml(day) + '</span></div>';
                lastDay = day;
            }
            var mine = msg.is_mine || msg.sender_name === 'You';
            html += '<div class="msg-wrap' + (mine ? ' mine' : '') + '">';
            if (!mine) {
                html += '<div class="sender">' + escapeHtml(msg.sender_name) + '</div>';
            }
            html += '<div class="bubble">' + linkify(msg.message) +
                '<span class="msg-time">' + escapeHtml(formatDisplayTime(msg.date)) + '</span></div></div>';
        }

        if (prepend) {
            var oldScroll = box.scrollHeight;
            var btn = $('load-more-btn');
            var extra = html;
            if (btn) {
                btn.insertAdjacentHTML ? btn.insertAdjacentHTML('afterend', extra) : (btn.outerHTML += extra);
            }
            box.scrollTop = box.scrollHeight - oldScroll;
        } else {
            box.innerHTML = html;
            var loadBtn = $('load-more-btn');
            if (loadBtn) {
                loadBtn.onclick = function() { loadMoreMessages(); };
            }
            box.scrollTop = box.scrollHeight;
        }
    }

    function fetchMessages(chatId, quiet) {
        if (!chatId) return;
        if (!quiet) showMsgLoading('Loading messages...');
        xhr('GET', '/get_messages?chat_id=' + encodeURIComponent(chatId) + '&count=' + msgCount, null, function(status, data) {
            loadingRoomId = null;
            hideMsgLoading();
            renderRooms();
            if (status !== 200 || !data) {
                if (!quiet) {
                    $('messages').innerHTML = '<div class="empty-state">Failed to load messages</div>';
                }
                return;
            }
            if (!data.length) {
                $('messages').innerHTML = '<div class="empty-state">No messages yet — say hello!</div>';
                return;
            }
            markRoomActive(chatId, data[0].id || '');
            renderMessages(data, false);
        });
    }

    function refreshMessages() {
        if (!selectedChatId) return;
        var btn = $('btn-refresh-msg');
        btn.className = 'icon-btn spin';
        showMsgLoading('Refreshing...');
        xhr('GET', '/api/refresh_messages?chat_id=' + encodeURIComponent(selectedChatId) + '&count=' + msgCount, null, function(status, data) {
            btn.className = 'icon-btn';
            hideMsgLoading();
            if (status === 200 && data && data.messages) {
                if (!data.messages.length) {
                    $('messages').innerHTML = '<div class="empty-state">No messages yet</div>';
                } else {
                    renderMessages(data.messages, false);
                }
            }
        });
    }

    function loadMoreMessages() {
        msgCount += 40;
        refreshMessages();
    }

    function fetchRooms() {
        var container = $('rooms');
        container.innerHTML = '<div class="rooms-loading-bar"><div class="spinner-wheel"></div>Loading rooms...</div>';
        xhr('GET', '/get_rooms', null, function(status, data) {
            if (status !== 200 || !data) {
                $('rooms').innerHTML = '<div class="empty-state">Could not load rooms</div>';
                return;
            }
            if (data.status === 'error') {
                $('rooms').innerHTML = '<div class="empty-state">' + escapeHtml(data.message || 'Error') + '</div>';
                return;
            }
            roomsData = data;
            mergeUnreadFromRooms();
            renderRooms();
        });
    }

    function sendMessage() {
        var input = $('message-input');
        var text = (input.value || '').trim();
        if (!selectedChatId || !text) {
            if (!selectedChatId) alert('Select a room first');
            return;
        }
        var btn = $('send-btn');
        btn.disabled = true;
        input.value = '';
        xhr('POST', '/send_message', JSON.stringify({ chat_id: selectedChatId, message: text }), function(status, data) {
            btn.disabled = false;
            if (status === 200) {
                refreshMessages();
                fetchRooms();
                pollUnread();
            } else {
                alert((data && data.message) ? data.message : 'Send failed');
                input.value = text;
            }
        });
    }

    function startPolling() {
        if (pollTimer) clearInterval(pollTimer);
        pollTimer = setInterval(function() {
            if (selectedChatId) {
                xhr('GET', '/api/refresh_messages?chat_id=' + encodeURIComponent(selectedChatId) + '&count=' + msgCount, null, function(status, data) {
                    if (status === 200 && data && data.messages && data.messages.length && !msgLoading) {
                        renderMessages(data.messages, false);
                    }
                });
            }
            updateStatus();
            pollUnread();
        }, 30000);
    }

    function logout() {
        if (!confirm('Log out and clear saved credentials?')) return;
        xhr('POST', '/api/logout', '{}', function(status, data) {
            if (data && data.next) {
                window.location.href = data.next;
            } else {
                window.location.href = '/start_auth';
            }
        });
    }

    function toggleMenu() {
        var panel = $('menu-panel');
        panel.className = panel.className.indexOf('show') >= 0 ? 'menu-panel' : 'menu-panel show';
    }

    function bindEvents() {
        $('btn-menu').onclick = toggleSidebar;
        $('overlay').onclick = function() { setSidebar(false); };
        $('btn-more').onclick = function(e) {
            e.stopPropagation();
            toggleMenu();
        };
        document.onclick = function(e) {
            var panel = $('menu-panel');
            if (panel.className.indexOf('show') >= 0 && e.target.id !== 'btn-more') {
                panel.className = 'menu-panel';
            }
        };
        $('btn-refresh-rooms').onclick = function() { fetchRooms(); };
        $('btn-refresh-chat').onclick = function() { refreshMessages(); };
        $('btn-refresh-msg').onclick = refreshMessages;
        $('btn-logout').onclick = logout;
        $('send-btn').onclick = sendMessage;
        $('message-input').onkeypress = function(e) {
            e = e || window.event;
            var key = e.key || e.keyCode;
            if (key === 'Enter' || key === 13) sendMessage();
        };
        $('search-input').oninput = renderRooms;
        $('notify-dismiss').onclick = function(e) {
            if (e && e.stopPropagation) e.stopPropagation();
            dismissCurrentAlert();
        };
        $('notify-bar').onclick = function(e) {
            if (e.target && (e.target.id === 'notify-dismiss' || e.target.className.indexOf('notify-dismiss') >= 0)) return;
            dismissCurrentAlert();
            setSidebar(true);
        };

        var tabs = $('tabs').getElementsByClassName('tab');
        var i;
        for (i = 0; i < tabs.length; i++) {
            tabs[i].onclick = function() {
                var j;
                for (j = 0; j < tabs.length; j++) tabs[j].className = 'tab';
                this.className = 'tab active';
                currentFilter = this.getAttribute('data-filter');
                renderRooms();
            };
        }
    }

    function init() {
        bindEvents();
        updateStatus();
        fetchRooms();
        pollUnread();
        setInterval(pollUnread, 12000);
        startPolling();
        if (window.innerWidth >= 769) {
            setSidebar(true);
        }
    }

    if (document.addEventListener) {
        document.addEventListener('DOMContentLoaded', init);
    } else {
        window.onload = init;
    }
})();
