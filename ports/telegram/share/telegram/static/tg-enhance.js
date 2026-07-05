/* Telegram BB10 UI enhancements v2.2 */
(function() {
    var currentAlert = null;
    var unreadMap = {};
    var pollTimer = null;
    var msgLoadTimer = null;

    function $(id) { return document.getElementById(id); }

    function xhr(method, url, body, cb) {
        var req = new XMLHttpRequest();
        req.open(method, url, true);
        if (body) req.setRequestHeader('Content-Type', 'application/json;charset=UTF-8');
        req.onreadystatechange = function() {
            if (req.readyState === 4) {
                var data = null;
                try { data = JSON.parse(req.responseText); } catch (e) {}
                if (cb) cb(req.status, data);
            }
        };
        req.send(body || null);
    }

    function escapeHtml(t) {
        if (!t) return '';
        return String(t).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
    }

    function showMsgLoading(text) {
        var el = $('tg-msg-loading');
        if (!el) return;
        var p = el.getElementsByTagName('p')[0];
        if (p) p.textContent = text || 'Loading messages...';
        el.className = 'tg-msg-loading show';
    }

    function hideMsgLoading() {
        var el = $('tg-msg-loading');
        if (el) el.className = 'tg-msg-loading';
        if (msgLoadTimer) {
            clearInterval(msgLoadTimer);
            msgLoadTimer = null;
        }
    }

    function markRoomActive(chatId, messageId) {
        xhr('POST', '/api/active_room', JSON.stringify({ chat_id: chatId || '' }), null);
        if (chatId) {
            xhr('POST', '/api/mark_read', JSON.stringify({
                chat_id: chatId,
                message_id: messageId || ''
            }), null);
            unreadMap[String(chatId)] = 0;
            updateUnreadBadge();
            updateRoomUnreadBadge(chatId, 0);
        }
    }

    function dismissCurrentAlert() {
        var bar = $('tg-notify-bar');
        if (bar) bar.className = 'tg-notify-bar';
        var payload = { alert_id: '', room_id: '' };
        if (currentAlert) {
            payload.alert_id = currentAlert.id || '';
            payload.room_id = currentAlert.room_id || '';
        }
        xhr('POST', '/api/dismiss_alert', JSON.stringify(payload), null);
        currentAlert = null;
    }

    function updateUnreadBadge() {
        var badge = $('tg-unread-badge');
        if (!badge) return;
        var total = 0;
        var k;
        for (k in unreadMap) {
            if (unreadMap.hasOwnProperty(k) && unreadMap[k] > 0) total += unreadMap[k];
        }
        if (total > 0) {
            badge.style.display = 'inline-block';
            badge.textContent = total > 99 ? '99+' : String(total);
        } else {
            badge.style.display = 'none';
        }
    }

    function updateRoomUnreadBadge(chatId, count) {
        var buttons = document.querySelectorAll('.room-button');
        var i, btn, rid, badge, name;
        for (i = 0; i < buttons.length; i++) {
            btn = buttons[i];
            rid = btn.getAttribute('data-id');
            if (String(rid) !== String(chatId)) continue;
            name = btn.getAttribute('data-room-name') || btn.textContent;
            badge = btn.querySelector('.tg-room-unread');
            if (count > 0) {
                btn.className = 'room-button tg-has-unread';
                if (!badge) {
                    btn.innerHTML = escapeHtml(name) + ' <span class="tg-room-unread">' +
                        (count > 9 ? '9+' : String(count)) + '</span>';
                } else {
                    badge.textContent = count > 9 ? '9+' : String(count);
                    badge.style.display = 'inline-block';
                }
            } else {
                btn.className = 'room-button';
                btn.innerHTML = escapeHtml(name);
            }
        }
    }

    function applyUnreadFromRooms(rooms) {
        var i, room;
        if (!rooms || !rooms.length) return;
        for (i = 0; i < rooms.length; i++) {
            room = rooms[i];
            if (room && room.id !== undefined) {
                unreadMap[String(room.id)] = room.unread || 0;
            }
        }
        updateUnreadBadge();
    }

    function showAlert(alert) {
        if (!alert || !alert.time) {
            var b = $('tg-notify-bar');
            if (b) b.className = 'tg-notify-bar';
            currentAlert = null;
            return;
        }
        if (typeof selectedChatId !== 'undefined' && String(alert.room_id) === String(selectedChatId)) {
            dismissCurrentAlert();
            return;
        }
        var bar = $('tg-notify-bar');
        var text = $('tg-notify-text');
        if (!bar || !text) return;
        text.innerHTML = '<strong>' + escapeHtml(alert.room) + '</strong> ' +
            escapeHtml(alert.from) + ': ' + escapeHtml(alert.text);
        bar.className = 'tg-notify-bar show';
        currentAlert = alert;
    }

    function pollUnread() {
        xhr('GET', '/api/unread', null, function(status, data) {
            if (status !== 200 || !data) return;
            if (data.unread) {
                var k;
                for (k in data.unread) {
                    if (data.unread.hasOwnProperty(k)) {
                        unreadMap[String(k)] = data.unread[k];
                    }
                }
            }
            updateUnreadBadge();
            if (data.alert) showAlert(data.alert);
            else {
                var bar = $('tg-notify-bar');
                if (bar) bar.className = 'tg-notify-bar';
                currentAlert = null;
            }
        });
        xhr('GET', '/api/status', null, function(status, data) {
            var dot = $('tg-status-dot');
            var txt = $('tg-status-text');
            if (!dot || !txt) return;
            if (status === 200 && data && data.connected) {
                dot.className = 'tg-status-dot ok';
                txt.textContent = 'Connected';
            } else {
                dot.className = 'tg-status-dot';
                txt.textContent = 'Offline';
            }
        });
    }

    function hasInitialLoadingDiv() {
        var m = $('messages');
        if (!m) return false;
        var blocks = m.getElementsByClassName('loading');
        return blocks && blocks.length > 0;
    }

    function wrapFetchMessages() {
        if (typeof fetchMessages !== 'function' || fetchMessages._tgWrapped) return;
        var orig = fetchMessages;
        fetchMessages = function(chat_id) {
            if (msgLoadTimer) clearInterval(msgLoadTimer);
            orig(chat_id);
            var checks = 0;
            msgLoadTimer = setInterval(function() {
                checks++;
                if (!hasInitialLoadingDiv() || checks > 40) {
                    clearInterval(msgLoadTimer);
                    msgLoadTimer = null;
                    hideMsgLoading();
                }
            }, 150);
        };
        fetchMessages._tgWrapped = true;
    }

    function hookRoomClicks() {
        var rooms = $('rooms');
        if (!rooms || rooms._tgHooked) return;
        rooms._tgHooked = true;
        rooms.addEventListener('click', function(e) {
            var btn = e.target;
            while (btn && btn.className.indexOf('room-button') < 0) btn = btn.parentNode;
            if (!btn) return;
            showMsgLoading('Loading messages...');
        }, true);
    }

    function bindNotifyBar() {
        var dismiss = $('tg-notify-dismiss');
        var bar = $('tg-notify-bar');
        if (dismiss) {
            dismiss.onclick = function(e) {
                if (e.stopPropagation) e.stopPropagation();
                dismissCurrentAlert();
                return false;
            };
        }
        if (bar) {
            bar.onclick = function(e) {
                if (e.target && e.target.id === 'tg-notify-dismiss') return;
                dismissCurrentAlert();
                if (typeof toggleSidebar === 'function' && !sidebarOpen) toggleSidebar();
            };
        }
    }

    window.tgRoomsRendered = function(rooms) {
        applyUnreadFromRooms(rooms);
    };

    window.tgMessagesLoaded = function(chatId) {
        hideMsgLoading();
        xhr('GET', '/get_messages?chat_id=' + encodeURIComponent(chatId), null, function(st, data) {
            if (st === 200 && data && data.length) {
                markRoomActive(chatId, data[0].id);
            } else {
                markRoomActive(chatId, '');
            }
        });
    };

    function init() {
        bindNotifyBar();
        hookRoomClicks();
        var oldOnload = window.onload;
        window.onload = function() {
            wrapFetchMessages();
            pollUnread();
            if (pollTimer) clearInterval(pollTimer);
            pollTimer = setInterval(pollUnread, 12000);
            if (oldOnload) oldOnload();
        };
        if (document.readyState === 'complete') {
            wrapFetchMessages();
        }
    }

    if (document.addEventListener) {
        document.addEventListener('DOMContentLoaded', function() {
            bindNotifyBar();
            hookRoomClicks();
        });
    }
    init();
})();
