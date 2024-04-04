#include "../minishell.h"

void	ft_pwd(t_var *exec, t_env *env)
{
	t_env	*tmp;

	tmp = ft_lstfind_env(&env, "PWD", NULL);
	ft_putstr_fd(tmp->line + 4, exec->f_out);
	ft_putstr_fd("\n", exec->f_out);
	// return ;
	exit(89); // 0
}
