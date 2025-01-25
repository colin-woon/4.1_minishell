#include "minishell.h"

int	current_directory(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		g_last_exit_code = 1;
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

int main(int ac, char **av)
{
	(void) ac;
	char *input = av[1];

	if (!ft_strncmp(input, "pwd", 4))
	{
		current_directory(NULL);
	}
}
