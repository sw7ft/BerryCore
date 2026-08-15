# Term49 launch splash — sourced from ~/.profile (POSIX sh, 256-color)
# Re-run anytime: term49_splash

term49_theme() {
    if [ -t 1 ] || [ "${TERM49_SPLASH_FORCE:-0}" = "1" ]; then
        # Match share/term48rc: deep berry void + pale orchid text
        printf '\033]11;rgb:0800/0000/1200\007'
        printf '\033]10;rgb:ec00/e400/ff00\007'
        printf '\033]12;rgb:ff00/6e00/c800\007'
    fi
}

term49_splash() {
    [ -t 1 ] || [ "${TERM49_SPLASH_FORCE:-0}" = "1" ] || return 0

    _rst='\033[0m'
    _dim='\033[38;5;60m'
    _lbl='\033[38;5;183m'
    _acc='\033[1;38;5;213m'
    _cyn='\033[1;38;5;51m'
    _pnk='\033[1;38;5;207m'
    _prp='\033[1;38;5;141m'
    _org='\033[1;38;5;215m'
    _wht='\033[1;38;5;231m'
    _mut='\033[38;5;146m'
    _box='\033[38;5;93m'
    _g1='\033[1;38;5;201m'
    _g2='\033[1;38;5;207m'
    _g3='\033[1;38;5;213m'
    _g4='\033[1;38;5;177m'
    _g5='\033[1;38;5;141m'
    _g6='\033[1;38;5;147m'

    _ver="?"
    [ -n "$NATIVE_TOOLS" ] && [ -f "$NATIVE_TOOLS/VERSION" ] && _ver=$(cat "$NATIVE_TOOLS/VERSION")
    _host=$(hostname 2>/dev/null || echo Passport)
    _when=$(date '+%a %b %d  %H:%M' 2>/dev/null || echo "")

    term49_theme
    printf '\033[2J\033[H'

    printf "\n"
    printf "  ${_g1}████████╗${_g2}███████╗${_g3}██████╗ ${_g4}███╗   ███╗${_g5}██╗  ██╗${_g6} █████╗${_rst}\n"
    printf "  ${_g1}╚══██╔══╝${_g2}██╔════╝${_g3}██╔══██╗${_g4}████╗ ████║${_g5}██║  ██║${_g6}██╔══██╗${_rst}\n"
    printf "  ${_g1}   ██║   ${_g2}█████╗  ${_g3}██████╔╝${_g4}██╔████╔██║${_g5}███████║${_g6}╚██████║${_rst}\n"
    printf "  ${_g1}   ██║   ${_g2}██╔══╝  ${_g3}██╔══██╗${_g4}██║╚██╔╝██║${_g5}╚════██║${_g6} ╚═══██║${_rst}\n"
    printf "  ${_g1}   ██║   ${_g2}███████╗${_g3}██║  ██║${_g4}██║ ╚═╝ ██║${_g5}     ██║${_g6} █████╔╝${_rst}\n"
    printf "  ${_g1}   ╚═╝   ${_g2}╚══════╝${_g3}╚═╝  ╚═╝${_g4}╚═╝     ╚═╝${_g5}     ╚═╝${_g6} ╚════╝${_rst}\n"
    printf "\n"
    printf "     ${_pnk}✦${_rst} ${_wht}B E R R Y C O R E${_rst}  ${_dim}·${_rst}  ${_cyn}Q N X  U S E R L A N D${_rst} ${_pnk}✦${_rst}\n"
    printf "\n"
    printf "   ${_org}v%s${_rst}  ${_dim}│${_rst}  ${_lbl}%s${_rst}  ${_dim}│${_rst}  ${_mut}%s${_rst}\n" "$_ver" "$_host" "$_when"
    printf "  ${_box}──────────────────────────────────────────────────${_rst}\n"
    printf "  ${_acc}qpkg${_rst} ${_mut}catalog · install · ports · bins${_rst}\n"
    printf "  ${_acc}jump${_rst} ${_mut}misc · docs · downloads · sdcard · bc${_rst}\n"
    printf "  ${_acc}run${_rst}  ${_mut}linux · games · nano · vim · settings${_rst}\n"
    printf "  ${_box}──────────────────────────────────────────────────${_rst}\n"
    printf "  ${_prp}metamode${_rst} ${_dim}tap top-left or hold space${_rst}\n"
    printf "  ${_dim}hjkl arrows · c ctrl · a alt · v paste · e esc${_rst}\n"
    printf "\n"

    unset _rst _dim _lbl _acc _cyn _pnk _prp _org _wht _mut _box
    unset _g1 _g2 _g3 _g4 _g5 _g6 _ver _host _when
}

alias splash='term49_splash'
alias term49='term49_splash'
