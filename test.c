#include "minishell.h"

int main(int ac, char **av)
{
	(void) ac;
	char *input = av[1];

	if (!ft_strncmp(input, "echo", 4))
	{
		printf("this is %s\n",input);
	}
}
