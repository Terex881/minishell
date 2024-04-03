#include "minishell.h"
#include <stdio.h>

void ft_signal_c(int num)
{
    if (num == SIGINT)
	{
		rl_clear_history();
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
    }
	if (num == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			tcsetattr(STDIN_FILENO, TCSANOW, &original_terminos);
	}
}

void ft_signal()
{
    signal(SIGINT, ft_signal_c);
    signal(SIGQUIT, ft_signal_c);
}

// void leak(){system("leaks minishell");}

int	main(int ac, char **av, char **env)
{
	// atexit(leak);
	(void)ac;
	(void)av;
	t_list	*list;
	t_data	*data;

	rl_catch_signals = 0;
	tcgetattr(STDIN_FILENO, &original_terminos);
	list = NULL;
	t_env *env1 = ft_get_env(&data, env);
	
	ft_all(&list, env1, data);
}