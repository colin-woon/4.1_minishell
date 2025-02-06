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

run_test() {
    DESCRIPTION="$1"
    TEST="$2"
    echo "${BLUE}${DESCRIPTION}${END} ${GREEN}${TEST}${END}"
    ../minishell -debug "${TEST}"
    echo
}

run_test '-----------ECHO-------------' 'echo "hello world '\''im'\'' a sigma"'
# echo "${BLUE}BUILTINS${END}"
# DESCRIPTION='---------PWD----------'
# TEST='pwd'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug ${TEST}
# echo

# DESCRIPTION='PWD with a flag'
# TEST='pwd -asdsd'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='PWD with random values'
# TEST="pwd asd -asdsd"
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='-----------ECHO-------------'
# TEST="'echo "hello world im a sigma"'"
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH VALID VAR IN DOUBLE QUOTES'
# TEST='echo hello world "\$USER" is a sigma'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH INVALID VAR IN DOUBLE QUOTES'
# TEST='echo hello world "$SNOOP_DOG" is a sigma'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH JUST VAR SYMBOL IN DOUBLE QUOTES'
# TEST='echo hello world "$" is a sigma'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH VALID VAR IN DOUBLE QUOTES BUT SURROUNDED WITH SINGLE QUOTES'
# TEST="echo 'hello world "\$USER" is a sigma'"
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH INVALID VAR IN DOUBLE QUOTES BUT SURROUNDED WITH SINGLE QUOTES'
# TEST="echo 'hello world "\$OBAMA" is a sigma'"
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH JUST VAR SYMBOL IN DOUBLE QUOTES BUT SURROUNDED WITH SINGLE QUOTES'
# TEST="echo 'hello world "\$" is a sigma'"
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH VALID VAR IN SINGLE QUOTES BUT SURROUNDED WITH DOUBLE QUOTES'
# TEST='echo "hello world '\$USER' is a sigma"'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH INVALID VAR IN SINGLE QUOTES BUT SURROUNDED WITH DOUBLE QUOTES'
# TEST='echo "hello world '\$TRUMP' is a sigma"'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WITH JUST VAR SYMBOL IN SINGLE QUOTES BUT SURROUNDED WITH DOUBLE QUOTES'
# TEST='echo "hello world '\$' is a sigma"'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='JUST VAR SYMBOL'
# TEST='echo hello world $ is a sigma'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='VALID VAR'
# TEST='echo hello world $USER is a sigma'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='INVALID VAR'
# TEST='echo hello world $ASHKETCHUM is a sigma'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='WEIRD VAR'
# TEST='echo hello world $= is a sigma'
# echo "${GREEN}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# # ERROR
# echo "${RED}ERRORS${END}"
# DESCRIPTION='UNCLOSED DOUBLE QUOTE'
# TEST='"echo hello""'
# echo "${ORANGE}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='UNCLOSED SINGLE QUOTE'
# TEST="'echo hello''"
# echo "${ORANGE}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# ESCRIPTION='fake_command'
# TEST='fake_command'
# echo "${RED}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='bin/fake_command'
# TEST='bin/fake_command'
# echo "${RED}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='PIPED command with error'
# TEST='ls | ls | imposter | ls'
# echo "${RED}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='ABSOLUTE path'
# TEST='/bin/ls -l -a'
# echo "${ORANGE}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='RELATIVE path'
# TEST='ls -la'
# echo "${ORANGE}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='PIPED command'
# TEST='ls | ls | ls | ls'
# echo "${ORANGE}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# DESCRIPTION='PIPED command'
# TEST='ls | ls | ls | ls'
# echo "${ORANGE}${DESCRIPTION} ${TEST}${END}"
# ../minishell -debug "${TEST}"
# echo

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1
