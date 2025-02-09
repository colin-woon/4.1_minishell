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

echo "${ORANGE}-----------------PWD-----------------${END}"
run_test '-----------PWD-------------' 'pwd'
run_test '-----------PWD with FLAGS-------------' 'pwd -a'
run_test '-----------PWD but unset $PWD env-------------' 'unset PWD'
unset PWD
run_test '-----------PWD but unset $PWD env-------------' 'pwd'
cd .

echo "\n${ORANGE}-----------------ENV-----------------${END}"
run_test '-----------ENV-------------' 'env'
run_test '-----------ENV with FLAGS-------------' 'env -abc -defg'

echo "\n${ORANGE}-----------------EXPORT-----------------${END}"
run_test '-----------EXPORT-------------' 'export'
run_test '----------EXPORT single var----------' 'export FRUIT=apple'
run_test '----------EXPORT multiple vars----------' 'export ONE=1 TWO=2'
run_test '----------EXPORT empty value----------' 'export EMPTY='
run_test '----------EXPORT invalid name----------' 'export 1invalid=test'
run_test '----------EXPORT existing var----------' 'export PATH=/some/new/path'

echo "\n${ORANGE}-----------------UNSET-----------------${END}"
run_test 'UNSET existing var' 'export MYVAR=123 unset MYVAR env'
run_test 'UNSET multiple vars' 'export MYVAR=123 MYVAR2=456'
run_test 'UNSET invalid var' 'unset 1234ABCDEF'

echo "\n${ORANGE}-----------------CD-----------------${END}"
run_test 'CD to root' 'cd /'
run_test 'CD to home' 'cd ~'
run_test 'CD relative path' 'cd ../'
run_test 'CD invalid directory' 'cd /some/nonexistent/path'
run_test 'CD with no args (home)' 'cd'

echo "\n${ORANGE}-----------------ECHO-----------------${END}"
run_test 'ECHO with no args' 'echo'
run_test 'ECHO with text' 'echo Hello World'
run_test 'ECHO with -n flag' 'echo -n NoNewLine'
run_test 'ECHO with quotes' 'echo "'\''Quoted text'\''"'

echo "\n${ORANGE}-----------------EXIT-----------------${END}"
run_test 'EXIT with no args' 'exit'
run_test 'EXIT with numeric arg' 'exit 42'
run_test 'EXIT with multiple args' 'exit 1 2 3'
run_test 'EXIT with non-numeric arg' 'exit abc'

