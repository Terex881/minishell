#include "minishell.h"
#include <stdio.h>

void ft_signal_c(int num)
{
    if (num == SIGINT)
	{
		// rl_clear_history();//🌸
		// write(1, "\n", 1);//🌸
		// rl_on_new_line();//🌸
		// rl_replace_line("", 0);//🌸
		// rl_redisplay();//🌸
    }
}

void ft_signal()
{
    signal(SIGINT, ft_signal_c);
    signal(SIGQUIT, ft_signal_c);
}

// void ft_fill_data(t_data **data, char **env)
// {

// 	*data = (t_data *)malloc(sizeof(t_data));
// 	if(!*data)
// 		return ;
// 	(*data)->env = ft_get_env(env);
	
// 	(*data)->path = ft_get_line((*data), "PATH", 5);
	
// 	// if(!data)
// 	// 	return (NULL);
// 	// data->old_pwd = ft_get_line(data, "PWD", 4);
// 	// data->old_pwd = getcwd(NULL, 0);
// 	// return ((*data)->path);
// }
int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_list	*list;
	t_data	*data;



	// rl_catch_signals = 0;//🌸
	list = NULL;
	ft_get_env(&data, env);
	// ft_fill_data(&data, env);
	// while (data->env)
	// {
	// 	printf("%s\n", data->env->line);
	// 	data->env = data->env->next;
	// }
	// printf("%s\n", data->path);
	ft_all(&list, env, data);
}
