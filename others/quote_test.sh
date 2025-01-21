# substitute
echo "hello '$fake' world"
echo "hello '$PAGER' world"
echo "hello "$" world"
echo "hello "$fake" world"
echo "hello "$PAGER" world"
# echo 'hello '$' world'  (literal)
echo 'hello '$fake' world'
echo 'hello '$PAGER' world'
# echo hello "$fake" world (incorrect spacing)
echo hello "$PAGER" world
echo hello $fake world
echo hello $PAGER world

# literal
echo "hello '$' world"
echo 'hello "$" world'
echo 'hello "$fake" world'
echo 'hello "$PAGER" world'
# echo hello "$" world (substituted)
echo hello '$' world
echo hello '$fake' world
echo hello '$PAGER' world
echo hello $ world




# echo "hello '$' world"
# echo "hello '$fake' world"
# echo "hello '$PAGER' world"
# echo "hello "$" world"
# echo "hello "$fake" world"
# echo "hello "$PAGER" world"
# echo 'hello '$' world'
# echo 'hello '$fake' world'
# echo 'hello '$PAGER' world'
# echo 'hello "$" world'
# echo 'hello "$fake" world'
# echo 'hello "$PAGER" world'
# echo hello "$" world
# echo hello "$fake" world
# echo hello "$PAGER" world
# echo hello '$' world
# echo hello '$fake' world
# echo hello '$PAGER' world
# echo hello $ world
# echo hello $fake world
# echo hello $PAGER world

# hello '$' world
# hello '' world
# hello 'less' world
# hello $ world
# hello  world
# hello less world
# hello $ world
# hello  world
# hello less world
# hello "$" world
# hello "$fake" world
# hello "$PAGER" world
# hello $ world
# hello  world
# hello less world
# hello $ world
# hello $fake world
# hello $PAGER world
# hello $ world
# hello world
# hello less world


$ echo $PAGERhello

$ echo $PAGER$ hello
less$ hello
$ echo $PAGER$hello
less
