#include "../minishell.h"

void	ft_pwd(t_var *exec, t_env *env)
{
	char	*tmp;

	// tmp = ft_lstfind_env(&env, "PWD", NULL);
	tmp = getcwd(NULL, 0);
	// if (!tmp)
	// {
	// 	ft_error("minishell: pwd: ", NULL, strerror(errno));
	// 	exec->status = 1;
	// 	return ;
	// }
	ft_putstr_fd(tmp, exec->f_out);
	ft_putstr_fd("\n", exec->f_out);
	// free(tmp);
	return ;
}
