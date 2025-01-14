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

echo "${YELLOW}PRINT TOKEN TO SEE${END}"
# echo "${BLUE}Mixed Quotes${END}"
# echo "${BLUE}INPUT: echo 'ab 'cd' ef'${END}"
# ../minishell -debug "echo 'ab 'cd' ef'"
# echo
echo "${BLUE}SINGLE Quotes${END}"
../minishell -debug "echo 'hello \$PAGER world'"
echo
echo "${BLUE}DOUBLE Quotes${END}"
../minishell -debug "echo \"hello \$PAGER world\""
echo
# echo "${BLUE}DOUBLE Quote containing SINGLE quote${END}"
# echo "${ORANGE}INPUT: \"hello '\$PAGER' world\"${END}"
# echo "${GREEN}OUTPUT: hello 'less' world${END}"
# ../minishell -debug "echo \"hello '\$PAGER' world\""
# echo
# echo "${RED}DOUBLE Quote containing DOUBLE quote${END}"
# ../minishell -debug "echo \"hello \"\$PAGER\" world\""
# echo
# echo "${BLUE}SINGLE Quote containing SINGLE quote${END}"
# echo "${ORANGE}INPUT: 'hello '\$PAGER' world'${END}"
# echo "${GREEN}OUTPUT: hello less world${END}"
# ../minishell -debug "echo 'hello '\$PAGER' world'"
# echo
# echo "${BLUE}SINGLE Quote containing DOUBLE quote${END}"
# ../minishell -debug "echo 'hello \"\$PAGER\" world'"
# echo

# ~ echo 'hello 'hi' world'
# hello hi world
# ~ echo "hello "hi" world"
# hello hi world
# ~ echo 'hello "hi" world'
# hello "hi" world
# ~ echo "hello 'hi' world"
# hello 'hi' world

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1
