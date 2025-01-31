
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

echo "${ORANGE}INPUT: /bin/ls ABSOLUTE path${END}"
../minishell -debug "/bin/ls -l -a"
echo
echo "${ORANGE}INPUT: ls RELATIVE path${END}"
../minishell -debug "ls -la"
echo
echo "${ORANGE}INPUT: ls PIPED command${END}"
../minishell -debug "ls | ls | ls | ls"
echo
echo "${RED}INPUT: fake_command ${END}"
../minishell -debug "fake_command"
echo
echo "${RED}INPUT: bin/fake_command ${END}"
../minishell -debug "bin/fake_command"
echo
echo "${RED}INPUT: ls PIPED command with error${END}"
../minishell -debug "ls | ls | imposter | ls"
echo

# silences the command
make fclean -C "$MAKEFILE_DIR" > /dev/null 2>&1
