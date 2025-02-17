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
run_test 'ABSOLUTE path' '/bin/ls -l -a | wc -l'
run_test 'RELATIVE path' 'ls -la | wc -l'
run_test 'PIPED command' 'ls | ls | ls | ls'
run_test 'Extra spaces' '   ls     -l    -a   '


run_test '-----------REDIRECTIONS------------' ''
run_test '-----------REDIRECT IN------------' ''
touch test_redir_in
run_test '------EMPTY FILE-------' 'cat < test_redir_in'

echo "redirect in works" > test_redir_in
run_test '-----NORMAL-----' 'cat < test_redir_in'

echo "redirect with spaces in works" > "test redir in"
run_test '------FILENAME WITH SPACES-------' 'cat < "test redir in"'

echo 'SHOULD SHOW redirect in works'
run_test '------MULTIPLE REDIR IN-------' 'cat < "test redir in" < test_redir_in'
rm -rf "test redir in"

run_test '------EMPTY-------' 'cat < /dev/null'

mkdir a_directory
run_test '------ERROR DIRECTORY------' 'cat < a_directory'
rm -rf a_directory

run_test '------ERROR COMMAND-------' 'fakecat < /dev/null'
run_test '------ERROR-------' 'cat < non_existent_file'
run_test '------ERROR NOT SUPPOSED TO REDIRECT-------' 'ls < test_redir_in'



run_test '-----------REDIRECT OUT------------' 'echo > test_redir_out'
run_test '------NORMAL-------' 'echo "redirect out works" > test_redir_out | cat test_redir_out'

chmod -r test_redir_out
run_test '------FILE READ-ONLY-------' 'echo "redirect is trying to work again" > test_redir_out | cat test_redir_out'

mkdir a_directory
run_test '------ERROR DIRECTORY-------' 'echo "redirect is trying to work again" > a_directory | cat a_directory'
rm -rf a_directory

run_test '------EMPTY-------' 'echo "i should not print" > /dev/null'

chmod +r test_redir_out
run_test '------ERROR COMMAND-------' 'fakeecho "redirect is trying to work again" > test_redir_out'

cat test_redir_out
run_test '------MULTIPLE REDIR OUT-------' 'echo "only me" > test_redir_out > test_redir_out2'
run_test 'SHOULD BE EMPTY' 'cat test_redir_out'
run_test 'SHOULD SHOW only me' 'cat test_redir_out2'

run_test '-----------APPEND------------' 'echo "append works" >> test_redir_out | cat test_redir_out'

cat test_redir_out
run_test '------MULTIPLE APPEND-------' 'echo "only me" >> test_redir_out2 >> test_redir_out'
run_test 'SHOULD BE only me from last test' 'cat test_redir_out2'
run_test 'SHOULD SHOW only me and old contents' 'cat test_redir_out'

chmod -r test_redir_out
run_test '------FILE READ-ONLY-------' 'echo "append is trying to work again" >> test_redir_out | cat test_redir_out'

mkdir a_directory
run_test '------ERROR DIRECTORY-------' 'echo "append is trying to work again" >> a_directory | cat a_directory'
rm -rf a_directory



chmod +r test_redir_out
run_test '-----------COMBINATION IN & OUT------------' 'cat < test_redir_in > test_redir_out | cat test_redir_out'
run_test '-----------COMBINATION IN & APPEND------------' 'cat < test_redir_in >> test_redir_out | cat test_redir_out'
run_test '-----------COMBINATION IN & OUT W PIPE------------' 'cat < test_redir_out | grep "works" > filtered_output'
run_test '' 'cat filtered_output'

cat test_redir_out
run_test '------COMBINATION OUT(R) & APPEND(L)-------' 'echo "finally only me" >> test_redir_out2 > test_redir_out'
run_test 'SHOULD BE only me from last test' 'cat test_redir_out2'
run_test 'SHOULD SHOW finally only me' 'cat test_redir_out'

cat test_redir_out
run_test '------COMBINATION OUT(L) & APPEND(R)-------' 'echo "nothing is forever" > test_redir_out2 >> test_redir_out'
run_test 'SHOULD BE EMPTY' 'cat test_redir_out2'
run_test 'SHOULD SHOW finally only me & nothing is forever' 'cat test_redir_out'

echo "ADDITONAL TESTS"
run_test 'WEIRD ASS SEPERATORS' 'cat < | wc -l'
run_test 'WEIRD ASS SEPERATORS' 'cat << |'
run_test 'WEIRD ASS SEPERATORS' 'cat > | wc -l'
run_test 'WEIRD ASS SEPERATORS' 'cat >> |'
run_test 'WEIRD ASS SEPERATORS' 'cat <'
run_test 'WEIRD ASS SEPERATORS' 'cat <<'
run_test 'WEIRD ASS SEPERATORS' 'cat >'
run_test 'WEIRD ASS SEPERATORS' 'cat >>'
run_test 'WEIRD ASS SEPERATORS' 'pwd | >'
run_test 'WEIRD ASS SEPERATORS' 'pwd | <'
run_test 'WEIRD ASS SEPERATORS' 'pwd | >>'
run_test 'WEIRD ASS SEPERATORS' 'pwd | <<'

run_test 'empty files' 'cat /dev/urandom | head -1 > outs/test-$num.txt 2> outs/test-$num-tty.txt'
run_test 'consecutive redir out' 'cat Makefile > abc/file1 > abc/file2 > abc/file3'
run_test 'consecutive redir in' 'cat Makefile < abc/file1 < abc/file2 < abc/file3'
run_test 'consecutive append out' 'cat Makefile >> abc/file1 >> abc/file2 >> abc/file3'

run_test 'empty single quotes' ''\'''\'''
run_test 'empty double quotes' '""'

run_test 'substitute var with weird symbols' '"$USER.txt"'
run_test 'substitue var with underscore' '$_'

rm -rf test_redir_out
rm -rf test_redir_out2
rm -rf test_redir_in
rm -rf filtered_output

run_test 'Should SUB' 'echo $?'
run_test 'Should SUB' 'echo "$?"'
run_test 'Dont SUB' 'echo '\''$?'\'''

run_test 'Should SUB' 'echo $?abcd'
run_test 'Should SUB' 'echo "$?abcd"'
run_test 'Dont SUB' 'echo '\''$?abcd'\'''

run_test 'Correct: ?efgh' 'echo $abcd?efgh'
run_test 'Correct: ?efgh' 'echo "$abcd?efgh"'
run_test 'Correct: $abcd?efgh' 'echo '\''$abcd?efgh'\'''

run_test 'Should SUB' 'echo $PWD $HOME $SHELL'
run_test 'Should SUB' 'echo "$PWD $HOME $SHELL"'
run_test 'Dont SUB' 'echo '\''$PWD $HOME $SHELL'\'''

run_test 'Should SUB' 'echo $PWD$HOME$SHELL'
run_test 'Should SUB' 'echo "$PWD$HOME$SHELL"'
run_test 'Dont SUB' 'echo '\''$PWD$HOME$SHELL'\'''

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1
