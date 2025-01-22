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

echo "${YELLOW}PRINT COMMAND TO SEE${END}"
# echo "${BLUE}Normal command${END}"
# echo "${BLUE}INPUT: echo 'ab 'cd' ef'${END}"
# ../minishell -debug "echo 'ab 'cd' ef'"
# echo
echo "${BLUE}With PIPE${END}"
echo "${BLUE}INPUT: echo 'ab 'cd' ef' | echo "after piped"${END}"
../minishell -debug "echo 'ab 'cd' ef'| echo \"after piped\""
echo


# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1