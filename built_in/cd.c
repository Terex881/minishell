#include "../minishell.h"

// void    ft_change_dir(char *path, t_data *data, ...)
void	ft_cd(char *path, t_data *data)
{
	char	*tmp;
	char	*find;
	char	*pwd;
	char	*join;
	int		n;
	data->stat  = 0;

	if (!path || !*path || (path[0] == '~' && path[1] == '\0'))
	{
		// free(path);
		tmp = ft_lstfind_env(&data->env, "HOME", NULL);
		path = ft_strdup(tmp + 5);
		// free(tmp);
	}
	tmp = ft_lstfind_env(&data->env, "PWD", NULL);
	n = chdir(path);
	pwd = getcwd(NULL, 0);
	if (!n && pwd)
	{
		free(pwd); // check this/////////////////////////////////////////////
		join = ft_strjoin("OLDPWD=", tmp + 4);
		find = ft_lstfind_env(&data->env, "OLDPWD", join);//add protection for strjoin
		// free(find);
		// free(join);
		pwd = getcwd(NULL, 0);
		join = ft_strjoin("PWD=", pwd);
		find = ft_lstfind_env(&data->env, "PWD", join);//add protection for strjoin
		// free(find);
		// free(join);
		// free(pwd);
	}
	else if (!n)
	{
		join = ft_strjoin("OLDPWD=", tmp + 4);
		find = ft_lstfind_env(&data->env, "OLDPWD", join);//add protection for strjoin
		// free(join);
		// free(find);
		join = ft_strjoin(tmp, "/..");
		find = ft_lstfind_env(&data->env, "PWD", join);//add protection for strjoin
		// free(join);
		// free(find);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		perror("path");
		printf("******\n");
		data->stat = 1;
	}
	// free(tmp);
	// free(path);
	// data->stat =0;
	free(pwd);
	return ;
}