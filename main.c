#include "minishell.h"

void ft_execution(t_var *exec, char **env)
{

}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*list;
	
	// rl_catch_signals = 0;
	list = NULL;
	ft_all(&list, env);
}
