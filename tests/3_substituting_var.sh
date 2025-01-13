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

# echo "${YELLOW}PRINT THE RESULT FROM FUNCTION GET_VARIABLE${END}"
# echo "${RED}SHOULDNT SUBSTITUTE${END}"
# ../minishell -debug "echo 'hello '$' world'"
# echo

echo "${GREEN}SHOULD SUBSTITUTE${END}"
echo "${BLUE}First${END}"
../minishell -debug "echo hello \"\$fake\" world"
echo
echo "${BLUE}Second${END}"
../minishell -debug "echo hello \"\$\" world"
echo
echo "${BLUE}Third${END}"
export EMPTY=
../minishell -debug "echo hello \$EMPTY world"
echo

# echo "${BLUE}SHOULD HAVE VALUE, memory leak is normal${END}"
# echo "${BLUE}INPUT: echo \"hello \$? asd\"${END}"
# ../minishell -debug "echo \"hello \$? asd\""
# echo
echo "${BLUE}INPUT: echo \"hello \$PAGER asd\"${END}"
../minishell -debug "echo \"hello \$PAGER asd\""
echo
# echo "${BLUE}INPUT: echo \"hello \$WSLENV asd\"${END}"
# ../minishell -debug "echo \"hello \$WSLENV asd\""
# echo


# echo "${ORANGE}SHOULDNT HAVE VALUE${END}"
# echo "${ORANGE}INPUT: echo \"hello \$world asd\"${END}"
# ../minishell -debug "echo \"hello \$world asd\""
# echo
# echo "${ORANGE}INPUT: echo \"hello \$WSL asd\"${END}"
# ../minishell -debug "echo \"hello \$WSL asd\""
# echo


# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1

# 4.1_minishell [main●] echo $PAGER
# less
# 4.1_minishell [main●] echo '$PAGER'
# $PAGER
# 4.1_minishell [main●] echo "$PAGER"
# less
# 4.1_minishell [main●] echo "hello $PAGER"
# hello less
# 4.1_minishell [main●] echo "hello '$PAGER'"
# hello 'less'
# 4.1_minishell [main●] echo "hello "$PAGER""
# hello less
# 4.1_minishell [main●] echo "hello" "$PAGER"
# hello less

# ~/42_core_program/4.1_minishell (main)*$ cat << abc
# > echo $PAGER
# > abc
# echo less
