# DEBUG FORMAT:
# ../minishell -debug "<input-command>"
# best to use double quotes to ignore spaces as seperate commands, will need to use \ if want to include double quotes

RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
ORANGE='\033[38;5;214m'
BLUE='\033[34m'
END='\033[0m'

MAKEFILE_DIR="../"
MINISHELL_EXEC="../minishell"

make -C "$MAKEFILE_DIR"
echo

# echo "${YELLOW}PRINT COMMAND TO SEE${END}"

# echo "${BLUE}PARSE WORD OR VARIABLE${END}"
# echo "${BLUE}WORD${END}"
# echo "${BLUE}INPUT: echo 'ab 'cd' ef'${END}"
# ../minishell -debug "echo 'ab 'cd' ef'"
# echo
# echo "${BLUE}VARIABLE${END}"
# echo "${BLUE}INPUT: echo \"hello \$PAGER world\"${END}"
# ../minishell -debug "echo \"hello \$PAGER world\""
# echo

# echo "${BLUE}PARSE PIPE${END}"
# echo "${BLUE}With PIPE${END}"
# echo "${BLUE}INPUT: echo 'ab 'cd' ef' | echo \"after piped\"${END}"
# ../minishell -debug "echo 'ab 'cd' ef'| echo \"after piped\""
# echo

# echo "${BLUE}PARSE REDIRECT_IN${END}"
# echo "${RED}TEST ERROR${END}"
# echo "${ORANGE}INPUT: cat < fakefile.txt ${END}"
# ../minishell -debug "cat < fakefile.txt "
# echo

# echo "${RED}TEST FILE${END}"
# echo "${ORANGE}INPUT: cat < infile.txt ${END}"
# touch infile.txt
# ../minishell -debug "cat < infile.txt "
# rm infile.txt
# echo

# echo "${BLUE}PARSE REDIRECT_OUT${END}"
# echo "${RED}TEST FILE${END}"
# echo "${ORANGE}INPUT: echo HI > outfile.txt ${END}"
# touch outfile.txt
# ../minishell -debug "echo HI > outfile.txt "
# rm outfile.txt
# echo

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1
