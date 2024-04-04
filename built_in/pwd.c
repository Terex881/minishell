#include "../minishell.h"

void	ft_pwd(t_var *exec, t_env *env)
{
	char	*tmp;

	tmp = ft_lstfind_env(&env, "PWD", NULL);
	if(!tmp)
		return;
	ft_putstr_fd(tmp + 4, exec->f_out);
	ft_putstr_fd("\n", exec->f_out);
	free(tmp);
	return ;
}