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
    echo "${BLUE}${DESCRIPTION}${END}"
	echo "${GREEN}${TEST}${END}"
    ../minishell -debug "${TEST}"
    echo
}

run_test '---------PWD----------' 'pwd'
run_test 'PWD with a flag' 'pwd -asdsd'
run_test 'PWD with random values' 'pwd asd -asdsd'

run_test '-----------ECHO-------------' 'echo "hello world im a sigma"'
run_test 'WITH VALID VAR IN DOUBLE QUOTES' 'echo hello world "\$USER" is a sigma'
run_test 'WITH INVALID VAR IN DOUBLE QUOTES' 'echo hello world "$SNOOP_DOG" is a sigma'
run_test 'WITH JUST VAR SYMBOL IN DOUBLE QUOTES' 'echo hello world "$" is a sigma'
run_test 'WITH VALID VAR IN DOUBLE QUOTES BUT SURROUNDED WITH SINGLE QUOTES' "echo 'hello world \"\$USER\" is a sigma'"
run_test 'WITH INVALID VAR IN DOUBLE QUOTES BUT SURROUNDED WITH SINGLE QUOTES' "echo 'hello world \"\$OBAMA\" is a sigma'"
run_test 'WITH JUST VAR SYMBOL IN DOUBLE QUOTES BUT SURROUNDED WITH SINGLE QUOTES' "echo 'hello world \"\$\" is a sigma'"
run_test 'WITH VALID VAR IN SINGLE QUOTES BUT SURROUNDED WITH DOUBLE QUOTES' 'echo "hello world '\''$USER'\'' is a sigma"'
run_test 'WITH INVALID VAR IN SINGLE QUOTES BUT SURROUNDED WITH DOUBLE QUOTES' 'echo "hello world '\''$TRUMP'\'' is a sigma"'
run_test 'WITH JUST VAR SYMBOL IN SINGLE QUOTES BUT SURROUNDED WITH DOUBLE QUOTES' 'echo "hello world '\''$'\'' is a sigma"'
run_test 'JUST VAR SYMBOL' 'echo hello world $ is a sigma'
run_test 'VALID VAR' 'echo hello world $USER is a sigma'
run_test 'INVALID VAR' 'echo hello world $ASHKETCHUM is a sigma'
run_test 'WEIRD VAR' 'echo hello world $= is a sigma'
run_test 'UNCLOSED DOUBLE QUOTE' '"echo hello""'
run_test 'UNCLOSED SINGLE QUOTE' "'echo hello''"

run_test '-----------COMMANDS------------' 'ls'
run_test 'fake_command' 'fake_command'
run_test 'bin/fake_command' 'bin/fake_command'
run_test 'PIPED command with error' 'ls | ls | imposter | ls'
run_test 'ABSOLUTE path' '/bin/ls -l -a'
run_test 'RELATIVE path' 'ls -la'
run_test 'PIPED command' 'ls | ls | ls | ls'

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1
