#include "minishell.h"
#include <sys/signal.h>


void ft_signal_c(int num)
{
    // if (num == SIGINT)
	// {
	// 	rl_clear_history();
	// 	write(1, "\n", 1);
	// 	rl_on_new_line();
	// 	rl_replace_line("", 0);
	// 	rl_redisplay();
    // }
}

void ft_signal()
{
    signal(SIGINT, ft_signal_c);
    signal(SIGQUIT, ft_signal_c);

}


int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*list;
	t_exit info;
	info.exitstat = 0;

	// rl_catch_signals = 0;
	list = NULL;
	ft_all(&list, env, info);
}
