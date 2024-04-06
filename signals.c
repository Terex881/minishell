#include "minishell.h"
#include <sys/fcntl.h>
#include <unistd.h>


void ft_signal_her(int num)
{
	close(0);	
}
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
}

void ft_signal()
{
    signal(SIGINT, ft_signal_c);
    signal(SIGQUIT, ft_signal_c);
}