#include "minishell.h"

// void    ft_change_dir(char *path, t_data *data, ...)
void	ft_cd(char *path, t_data *data)
{
	t_env	*tmp;
	int		n;

	if (!path || !*path || (path[0] == '~' && path[1] == '\0'))
		path = ft_lstfind_env(&data->env, "HOME", NULL)->line + 5;
	tmp = ft_lstfind_env(&data->env, "PWD", NULL);
	n = chdir(path);
	if (!n && getcwd(NULL, 0))
	{
		ft_lstfind_env(&data->env, "OLDPWD",
			ft_strjoin("OLDPWD=", tmp->line + 4));//add protection for strjoin
		ft_lstfind_env(&data->env, "PWD", ft_strjoin("PWD=", getcwd(NULL, 0)));//add protection for strjoin
	}
	else if (!n)
	{
		ft_lstfind_env(&data->env, "OLDPWD",
			ft_strjoin("OLDPWD=", tmp->line + 4));//add protection for strjoin
		ft_lstfind_env(&data->env, "PWD", ft_strjoin(tmp->line, "/.."));//add protection for strjoin
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		perror(path);
	}
	return ;
}