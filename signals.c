#include "minishell.h"



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