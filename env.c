#include "minishell.h" // ADD PATH to env, but dont print it if unset

void	ft_env(t_var *exec, t_data *data)
{
	t_env		*env;
	static int	i;

	if (!data->path)
	{
		perror("env");
		return ;
	}
	if (!i)
		ft_unset(exec, data, "OLDPWD");
	i++;
	env = data->env;
	while (env)
	{
		if (ft_strchr(env->line, '='))
		{
			ft_putstr_fd(env->line, exec->f_out);
			ft_putstr_fd("\n", exec->f_out);
		}
		env = env->next;
	}
}
