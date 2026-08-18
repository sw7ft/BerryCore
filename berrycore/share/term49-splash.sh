# BerryCore launch splash — sourced from ~/.profile (POSIX sh, 256-color)
# Re-run anytime: splash   (aliases: berrycore, term49)

berrycore_theme() {
    if [ -t 1 ] || [ "${TERM49_SPLASH_FORCE:-0}" = "1" ]; then
        # Match share/term48rc: deep navy + ice text
        printf '\033]11;rgb:0400/0c00/2000\007'
        printf '\033]10;rgb:c800/dc00/ff00\007'
        printf '\033]12;rgb:3d00/c400/ff00\007'
    fi
}

berrycore_splash() {
    [ -t 1 ] || [ "${TERM49_SPLASH_FORCE:-0}" = "1" ] || return 0

    # QNX has no /bin/printf — keep BerryCore/clitools on PATH (Term49 login).
    PATH="${NATIVE_TOOLS:-/accounts/1000/shared/misc/berrycore}/bin:/accounts/1000/shared/misc/clitools/bin:${PATH}"

    _rst='\033[0m'
    _ita='\033[3m'
    _dim='\033[38;5;60m'
    _lbl='\033[38;5;117m'
    _acc='\033[1;38;5;81m'
    _cyn='\033[1;38;5;51m'
    _ice='\033[1;38;5;159m'
    _blu='\033[1;38;5;75m'
    _sky='\033[1;38;5;123m'
    _wht='\033[1;38;5;231m'
    _mut='\033[38;5;109m'
    _box='\033[38;5;25m'
    _g1='\033[1;38;5;27m'
    _g2='\033[1;38;5;33m'
    _g3='\033[1;38;5;39m'
    _g4='\033[1;38;5;45m'
    _g5='\033[1;38;5;51m'

    _ver="?"
    [ -n "$NATIVE_TOOLS" ] && [ -f "$NATIVE_TOOLS/VERSION" ] && _ver=$(cat "$NATIVE_TOOLS/VERSION")
    _host=$(hostname 2>/dev/null || echo Passport)
    _when=$(date '+%a %b %d  %H:%M' 2>/dev/null || echo "")

    berrycore_theme
    printf '\033[2J\033[H'

    printf "\n"
    printf "  ${_g1}█▀▀▄${_rst} ${_g2}█▀▀▀${_rst} ${_g3}█▀▀▄${_rst} ${_g4}█▀▀▄${_rst} ${_g5}█  █${_rst} ${_g2}▄▀▀▄${_rst} ${_g3}▄▀▀▄${_rst} ${_g4}█▀▀▄${_rst} ${_g5}█▀▀▀${_rst}\n"
    printf "  ${_g1}█▀▀▄${_rst} ${_g2}█▀▀ ${_rst} ${_g3}█▀▀▄${_rst} ${_g4}█▀▀▄${_rst} ${_g5}▀▄▀ ${_rst} ${_g2}█   ${_rst} ${_g3}█  █${_rst} ${_g4}█▀▀▄${_rst} ${_g5}█▀▀ ${_rst}\n"
    printf "  ${_g1}█▄▄▀${_rst} ${_g2}█▄▄▄${_rst} ${_g3}█ ▀▄${_rst} ${_g4}█ ▀▄${_rst} ${_g5} █  ${_rst} ${_g2}▀▄▄▀${_rst} ${_g3}▀▄▄▀${_rst} ${_g4}█ ▀▄${_rst} ${_g5}█▄▄▄${_rst}\n"
    printf "\n"
    printf "     ${_ice}◆${_rst} ${_wht}Q N X  U S E R L A N D${_rst}  ${_dim}·${_rst}  ${_cyn}T E R M  4 9${_rst} ${_ice}◆${_rst}\n"
    printf "\n"
    printf "     ${_ita}${_cyn}Learn Systems to Control Systems${_rst}\n"
    printf "\n"
    printf "   ${_sky}v%s${_rst}  ${_dim}│${_rst}  ${_lbl}%s${_rst}  ${_dim}│${_rst}  ${_mut}%s${_rst}\n" "$_ver" "$_host" "$_when"
    printf "  ${_box}──────────────────────────────────────────────────${_rst}\n"
    printf "  ${_acc}%-10s${_rst} ${_mut}%s${_rst}\n" "qpkg" "catalog · install · ports · bins"
    printf "  ${_acc}%-10s${_rst} ${_mut}%s${_rst}\n" "apps" "http://127.0.0.1:8098/apps"
    printf "  ${_acc}%-10s${_rst} ${_mut}%s${_rst}\n" "shortcuts" "misc · docs · downloads · sdcard · bc"
    printf "  ${_acc}%-10s${_rst} ${_mut}%s${_rst}\n" "run" "setup · linux · games · nano · vim · settings"
    printf "  ${_box}──────────────────────────────────────────────────${_rst}\n"
    printf "  ${_blu}metamode${_rst} ${_dim}tap top-left or hold space${_rst}\n"
    printf "  ${_dim}hjkl arrows · c ctrl · a alt · v paste · e esc${_rst}\n"
    printf "\n"

    unset _rst _ita _dim _lbl _acc _cyn _ice _blu _sky _wht _mut _box
    unset _g1 _g2 _g3 _g4 _g5 _ver _host _when
}

term49_theme() { berrycore_theme; }
term49_splash() { berrycore_splash; }

alias splash='berrycore_splash'
alias berrycore='berrycore_splash'
alias term49='berrycore_splash'
