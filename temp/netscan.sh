#!/bin/bash
# Network Scanner Simulation

R='\033[0;31m'; G='\033[0;32m'; Y='\033[1;33m'
C='\033[0;36m'; W='\033[1;37m'; N='\033[0m'

clear
echo -e "${C}"
echo "╔══════════════════════════════════════════════╗"
echo "║     NETWORK RECONNAISSANCE INITIATED         ║"
echo "║        BerryCore Porsche Edition             ║"
echo "╚══════════════════════════════════════════════╝"
echo -e "${N}"
sleep 0.5

echo -e "${Y}[*] Scanning local network...${N}"
sleep 0.3

# Fake IP scan
ips=(
    "192.168.1.1|Router Gateway|OPEN"
    "192.168.1.10|Desktop PC|FILTERED"
    "192.168.1.15|Mobile Device|OPEN"
    "192.168.1.20|Smart TV|CLOSED"
    "192.168.1.100|Unknown Device|OPEN"
    "192.168.1.254|Access Point|OPEN"
)

echo ""
echo -e "${C}IP ADDRESS      │ DEVICE TYPE    │ STATUS${N}"
echo "────────────────┼────────────────┼──────────"

for entry in "${ips[@]}"; do
    IFS='|' read -r ip device status <<< "$entry"
    
    # Scanning animation
    echo -ne "${Y}Scanning... ${ip}${N}\r"
    sleep 0.3
    
    # Show result
    if [ "$status" = "OPEN" ]; then
        echo -e "${G}${ip}${N}    │ ${W}${device}${N}   │ ${G}${status}${N}"
    else
        echo -e "${Y}${ip}${N}    │ ${W}${device}${N}   │ ${Y}${status}${N}"
    fi
    sleep 0.2
done

echo ""
echo -e "${G}[✓] Scan complete${N}"
echo -e "${C}[i] ${W}6${N} hosts discovered"
echo -e "${C}[i] ${G}4${N} ports accessible"
echo ""








