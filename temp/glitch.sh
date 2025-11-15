#!/bin/bash
# Glitch Effect Status Display

R='\033[0;31m'; G='\033[0;32m'; Y='\033[1;33m'
C='\033[0;36m'; W='\033[1;37m'; N='\033[0m'

clear
# Glitch effect
for i in {1..5}; do
    clear
    echo -e "${R}█${G}▓${C}▒${Y}░${W} BERRYCORE PORSCHE ${Y}░${C}▒${G}▓${R}█${N}"
    sleep 0.1
    clear
    echo -e "${Y}░${C}▒${G}▓${R}█${W} BERRYCORE PORSCHE ${R}█${G}▓${C}▒${Y}░${N}"
    sleep 0.1
done

clear
echo -e "${W}╔═══════════════════════════════════════╗${N}"
echo -e "${W}║  ${C}>>> PORSCHE EDITION STATUS <<<${W}    ║${N}"
echo -e "${W}╚═══════════════════════════════════════╝${N}"
echo ""
echo -e "${G}[✓]${N} User      : ${Y}$(whoami)${N}"
echo -e "${G}[✓]${N} Host      : ${Y}$(hostname)${N}"
echo -e "${G}[✓]${N} Shell     : ${Y}${SHELL##*/}${N}"
echo -e "${G}[✓]${N} BerryCore : ${Y}${NATIVE_TOOLS:-Not Loaded}${N}"
echo -e "${G}[✓]${N} PWD       : ${Y}${PWD}${N}"
echo ""
echo -e "${C}[>]${N} Ready for action."
echo ""








