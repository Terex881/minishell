#include "minishell.h"

void ft_signal_c(int num)
{
    if (num == SIGINT)
	{

		// if(open(STDIN_FILENO, O_RDWR) == -1)
		// {
		// 	open(STDIN_FILENO, O_RDWR);
		// 	// printf("****\n");
		// 	return;
		// }
		rl_clear_history();

		write(1, "\n", 1);
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
    }






	// if (num == SIGQUIT)
	// {
	// 	if (waitpid(-1, NULL, WNOHANG) == 0)
	// 		tcsetattr(STDIN_FILENO, TCSANOW, &original_terminos);
	// }
}

void ft_signal()
{
    signal(SIGINT, ft_signal_c);
    signal(SIGQUIT, ft_signal_c);
}

// TERM_PROGRAM HOMEBREW_TEMP TERM SHELL TMPDIR TERM_PROGRAM_VERSION TERM_SESSION_ID ZSH USER LS_COLORS COMMAND_MODE SSH_AUTH_SOCK __CF_USER_TEXT_ENCODING PAGER HOMEBREW_CACHE LSCOLORS LaunchInstanceID PWD LANG ITERM_PROFILE XPC_FLAGS XPC_SERVICE_NAME SHLVL HOME COLORFGBG LC_TERMINAL_VERSION ITERM_SESSION_ID LESS LOGNAME LC_TERMINAL SECURITYSESSIONID COLORTERM ORIGINAL_XDG_CURRENT_DESKTOP GIT_ASKPASS VSCODE_GIT_ASKPASS_NODE VSCODE_GIT_ASKPASS_EXTRA_ARGS VSCODE_GIT_ASKPASS_MAIN VSCODE_GIT_IPC_HANDLE VSCODE_INJECTION ZDOTDIR USER_ZDOTDIR OLDPWD _