#include "minishell.h"

int	current_directory(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (0);
}

int	ft_env(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	if (!data->envp_array)
		return (EXIT_FAILURE);
	while (data->envp_array[i])
	{
		ft_putendl_fd(data->envp_array[i], 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	init_env(t_data *data, char **envp)
{
	int	total_env;
	int	i;

	total_env = 0;
	while (envp && envp[total_env])
		total_env++;
	data->envp_array = ft_calloc(total_env + 1, sizeof(char *));
	if (data->envp_array == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		data->envp_array[i] = ft_strdup(envp[i]);
		if (data->envp_array[i] == NULL)
			return ;
		i++;
	}
}

char	*get_env_var_value(t_data *data, char *key)
{
	int	i;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (data->envp_array[i])
	{
		if (ft_strncmp(tmp, data->envp_array[i], ft_strlen(key)) == 0)
		{
			free(tmp);
			return (ft_strchr(data->envp_array[i], '=') + 1);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

int	get_env_var_index(t_data *data, char *key)
{
	int	i;
	int	key_len;

	if (!data || !key)
		return (EXIT_FAILURE);
	key_len = ft_strlen(key);
	i = 0;
	while (data->envp_array[i])
	{
		if (!ft_strncmp(data->envp_array[i], key, key_len) && data->envp_array[i][key_len] == '=')
			return (i);
		i++;
	}
	return (EXIT_FAILURE);
}

int	set_env_var(t_data *data, char *key, char *value)
{
	int		index;
	char	*new_env;

	index = get_env_var_index(data, key);
	if (value)
		value = "";
	new_env = ft_strjoin("=", value);
	if (!new_env)
		return (EXIT_FAILURE);
	if (index != 1 && data->envp_array[index])
	{
		free(data->envp_array[index]);
		data->envp_array[index] = ft_strjoin(key, new_env);
	}
	else
	{
		index = 0;
		while (data->envp_array[index])
			index++;
		data->envp_array = realloc(data->envp_array, index + 1);
		if (!data->envp_array)
		{
			free(new_env);
			return (EXIT_FAILURE);
		}
		data->envp_array[index] = ft_strjoin(key, new_env);
	}
	free(new_env);
	return (EXIT_SUCCESS);
}
/*-------------------------------------------------------------------*/

static char	**get_key_value_pair(char *arg)
{
	char	*equal_sign_pos;
	char	**tmp;

	equal_sign_pos = ft_strchr(arg, '=');
	tmp = malloc(sizeof(tmp) * 3);
	tmp[0] = ft_substr(arg, 0, equal_sign_pos - arg);
	tmp[1] = ft_strdup(equal_sign_pos + 1);
	tmp[2] = NULL;
	return (tmp);
}

int	check_valid_env_var(char *env_var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(env_var[i]) && env_var[i] != '_')
		return (EXIT_FAILURE);
	i++;
	while (env_var[i])
	{
		if (!ft_isalnum(env_var[i]) && env_var[i] != '_')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int	a;
	char	**tmp;

	i = 1;
	a = i + 1;
	if (!args[a])
		return (ft_env(data, args));
	while (args[i])
	{
		if (!check_valid_env_var(args[i]))
		{
			//print_syntax_error(QUOTE_ERROR, args[i]);
			printf("error\n");
			return (EXIT_FAILURE);
		}
		else if (ft_strchr(args[i], '='))
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			ft_free_2d_array(tmp);
		}
	}
	return (EXIT_SUCCESS);
}

void	ft_update_envlst(t_data *data, char *key, char *value)
{
	set_env_var(data, "OLDPWD", get_env_var_value(data, "PWD"));
	set_env_var(data, "PWD", value);
	free(value);
}

int	change_dir(t_data *data, char *path)
{
	int	status;

	printf("path: %s\n", path);
	status = chdir(path);
	if (status == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		return (EXIT_FAILURE);
	}
	ft_update_envlst(data, "OLDPWD", getcwd(NULL, 0));
	return (EXIT_SUCCESS);
}

char	*get_home_path(t_data *data)
{
	int		i;
	char	*home;

	i = 0;
	while (data->envp_array[i])
	{
		if (!ft_strncmp(data->envp_array[i], "HOME=", 5))
		{
			home = ft_strdup(data->envp_array[i] + 5);
			return (home);
		}
		i++;
	}
	return (NULL);
}

int	ft_cd(t_data *data, char **args)
{
	char	*path;

	if (!args || !args[2] || args[2][0] == '\0')
	{
		path = get_home_path(data);
		if (!path)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (EXIT_FAILURE);
		}
		return (change_dir(data, path));
	}
	return (change_dir(data, args[2]));
}



int main(int ac, char **av, char **envp)
{
	(void) ac;
	char *input = av[1];
	t_data *data;

	init_env(data, envp);
	printf("OLDPWD: %s\n", get_env_var_value(data, "OLDPWD"));
	if (!ft_strncmp(input, "pwd", 4))
		current_directory(NULL);
	if (!ft_strncmp(input, "env", 3))
		ft_env(data, NULL);
	if (!ft_strncmp(input, "gethome", 7))
		get_home_path(data);
	if (!ft_strncmp(input, "cd", 2))
		ft_cd(data, av);
	if (!ft_strncmp(input, "export", 6))
		ft_export(data, av);
	printf("NEWPWD: %s\n", get_env_var_value(data, "PWD"));
	return (0);
}
