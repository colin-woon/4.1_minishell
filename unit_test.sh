# DEBUG FORMAT:
# ./minishell -debug "<input-command>"
# best to use double quotes to ignore spaces as seperate commands, will need to use \ if want to include double quotes

make
echo
# TOKENIZATION
echo "NORMAL COMMAND"
./minishell -debug "echo \"hello world\""
echo

echo "DETECTING SEPERATORS"
./minishell -debug "hi | < << > >>"
echo

echo "UNCLOSED DOUBLE QUOTE"
./minishell -debug "\"hi | < << > >>\"\""
echo

echo "MULTIPLE DOUBLE QUOTES"
./minishell -debug "\"hi | <\" << > >>\"\""
echo

echo "UNCLOSED SINGLE QUOTE"
./minishell -debug "'''"
echo

echo "MULTIPLE SINGLE QUOTES"
./minishell -debug "''''"
