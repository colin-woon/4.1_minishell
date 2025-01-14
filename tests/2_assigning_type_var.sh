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

# ASSIGNING EXPANDABLE VARIABLE TYPE
# PRINT TOKENS
echo "${GREEN}USE PRINT TOKENS TO CHECK${END}"
echo "${YELLOW}DETECTING VAR TYPE${END}"
../minishell -debug "hello \$PAR"
echo

# ERROR
echo "${RED}SHOULD BE ERRORS -- SYNTAX ERRORS${END}"
../minishell -debug "|"
../minishell -debug "<"
../minishell -debug "<<"
../minishell -debug ">"
../minishell -debug ">>"
../minishell -debug "asd |"
../minishell -debug "asd <"
../minishell -debug "asd <<"
../minishell -debug "asd >"
../minishell -debug "asd >>"

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1
