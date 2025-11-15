#!/bin/bash
# Matrix Rain Effect for BerryCore

GREEN='\033[0;32m'
LGREEN='\033[1;32m'
NC='\033[0m'

# Matrix characters
chars="01ﾊﾐﾋｰｳｼﾅﾓﾆｻﾜﾂｵﾘｱﾎﾃﾏｹﾒｴｶｷﾑﾕﾗｾﾈｽﾀﾇﾍ"

clear
echo -e "${GREEN}"

# Simple matrix rain
for i in {1..200}; do
    # Random column position (assuming 80 char width)
    col=$((RANDOM % 80))
    # Random character
    char_idx=$((RANDOM % ${#chars}))
    char="${chars:$char_idx:1}"
    
    # Position cursor and print character
    tput cup $((RANDOM % 20)) $col
    echo -ne "${LGREEN}${char}${NC}"
    
    sleep 0.01
done

echo -e "${NC}"
clear
echo -e "${GREEN}Wake up, Neo...${NC}"
echo -e "${GREEN}BerryCore has you...${NC}"
echo ""







