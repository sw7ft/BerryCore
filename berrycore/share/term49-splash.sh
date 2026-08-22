# BerryCore launch splash — sourced from ~/.profile (POSIX sh, 256-color)
# Canonical look: white 3-wide BERRYCORE on Ubuntu aubergine (#300A24).
# Re-run anytime: splash   (aliases: berrycore, term49)

berrycore_theme() {
    if [ -t 1 ] || [ "${TERM49_SPLASH_FORCE:-0}" = "1" ]; then
        # Dark Ubuntu aubergine (#300A24) + paper text + orange cursor
        printf '\033]11;rgb:3000/0a00/2400\007'
        printf '\033]10;rgb:ee00/ee00/ee00\007'
        printf '\033]12;rgb:e900/5400/2000\007'
    fi
}

berrycore_splash() {
    [ -t 1 ] || [ "${TERM49_SPLASH_FORCE:-0}" = "1" ] || return 0

    # QNX has no /bin/printf — keep BerryCore/clitools on PATH (Term49 login).
    PATH="${NATIVE_TOOLS:-/accounts/1000/shared/misc/berrycore}/bin:/accounts/1000/shared/misc/clitools/bin:${PATH}"

    _rst='\033[0m'
    _ita='\033[3m'
    _dim='\033[38;5;96m'
    _lbl='\033[38;5;183m'
    _acc='\033[1;38;5;177m'
    _cyn='\033[1;38;5;171m'
    _ice='\033[1;38;5;219m'
    _blu='\033[1;38;5;135m'
    _sky='\033[1;38;5;176m'
    _wht='\033[1;38;5;255m'
    _mut='\033[38;5;139m'
    _box='\033[38;5;89m'

    _ver="?"
    [ -n "$NATIVE_TOOLS" ] && [ -f "$NATIVE_TOOLS/VERSION" ] && _ver=$(cat "$NATIVE_TOOLS/VERSION")
    _host=$(hostname 2>/dev/null || echo Passport)
    _when=$(date '+%a %b %d  %H:%M' 2>/dev/null || echo "")

    berrycore_theme
    printf '\033[2J\033[H'

    printf "\n"
    printf "    ${_wht}█▀█ █▀▀ █▀█ █▀█ █ █ █▀▀ █▀█ █▀█ █▀▀${_rst}  ${_ice}● ●${_rst}\n"
    printf "    ${_wht}█▀█ █▀  █▀▄ █▀▄ ▀█▀ █   █ █ █▀▄ █▀ ${_rst} ${_ice}● ● ●${_rst}\n"
    printf "    ${_wht}█▄█ █▄▄ █ █ █ █  █  █▄▄ █▄█ █ █ █▄▄${_rst}  ${_ice}● ●${_rst}\n"
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
    unset _ver _host _when
}

term49_theme() { berrycore_theme; }
term49_splash() { berrycore_splash; }

alias splash='berrycore_splash'
alias berrycore='berrycore_splash'
alias term49='berrycore_splash'
