##Colours
  Red_t='\e[31m';
  Blue_t='\e[34m';
  Green_t='\e[32m';
  Lt_Red_t='\e[91m';
  Lt_Blue_t='\e[94m';
  Lt_Green_t='\e[92m';
  Dark_Grey_t='\e[90m';
  Lt_Grey_t='\e[37m';
  White_t='\e[97m';
  NC='\033[0m' # No Color
##Types
  Bold_t='\e[1m';
  Dim_t='\e[2m';
  Underlined_t='\e[4m';
  Blink_t='\e[5m';
  Hidden_t='\e[8m';
  RS='\e[0m'; #Reset all attributes
##LONSBERRY LOGO
  LONSBERRY_ENGINEERING='\e[41m LONSBERRY ENGINEERING \033[0m';


echo -e "\n\n${LONSBERRY_ENGINEERING}"
date
echo -e "\n  ${Underlined_t}TCP PORT FINDER${RS}\n\n"

echo -e "  Make sure the search_port.sh is under the same directory!\n" 

# read -p "    Press enter to continue";

./search_port.sh > result.txt





