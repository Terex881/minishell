#include "minishell.h"

// void	ft_unset(t_var *exec, t_data *data, char *line)
// {
// 	t_env	*p;
// 	t_env	*tmp;

// 	p = data->env;
// 	tmp = NULL;
// 	if (ft_strncmp(line, "PATH", 5) == 0)
// 		data->path = NULL;
// 	while (p)
// 	{
// 		if (ft_strncmp(p->line, line, ft_strlen(line)) == 0)
// 		{
// 			if (tmp)
// 				tmp->next = p->next;
// 			else
// 				data->env = p->next;
// 			ft_lstdelone_env(p);
// 			return ;
// 		}
// 		tmp = p;
// 		p = p->next;
// 	}
// }

// void	ft_cd(char *path, t_data *data)
// {
// 	t_env	*tmp;
// 	int		n;

// 	if (!path || !*path || (path[0] == '~' && path[1] == '\0'))
// 		path = ft_lstfind_env(&data->env, "HOME", NULL)->line + 5;
// 	tmp = ft_lstfind_env(&data->env, "PWD", NULL);
// 	n = chdir(path);
// 	if (!n && getcwd(NULL, 0))
// 	{
// 		ft_lstfind_env(&data->env, "OLDPWD",
// 			ft_strjoin("OLDPWD=", tmp->line + 4));//add protection for strjoin
// 		ft_lstfind_env(&data->env, "PWD", ft_strjoin("PWD=", getcwd(NULL, 0)));//add protection for strjoin
// 	}
// 	else if (!n)
// 	{
// 		ft_lstfind_env(&data->env, "OLDPWD",
// 			ft_strjoin("OLDPWD=", tmp->line + 4));//add protection for strjoin
// 		ft_lstfind_env(&data->env, "PWD", ft_strjoin(tmp->line, "/.."));//add protection for strjoin
// 	}
// 	else
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		perror(path);
// 	}
// 	return ;
// }

// void	ft_env(t_var *exec, t_data *data)
// {
// 	t_env		*env;
// 	static int	i;

// 	if (!i)
// 		ft_unset(exec, data, "OLDPWD");
// 	i++;
// 	env = data->env;
// 	while (env)
// 	{
// 		ft_putstr_fd(env->line, exec->f_out);
// 		ft_putstr_fd("\n", exec->f_out);
// 		env = env->next;
// 	}
// }

// void	ft_pwd(t_var *exec, t_env *env)
// {
// 	t_env	*tmp;

// 	tmp = ft_lstfind_env(&env, "PWD", NULL);
// 	ft_putstr_fd(tmp->line + 4, exec->f_out);
// 	ft_putstr_fd("\n", exec->f_out);
// 	return ;
// }
