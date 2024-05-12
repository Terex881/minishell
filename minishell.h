/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 23:20:05 by sdemnati          #+#    #+#             */
/*   Updated: 2024/05/12 09:37:14 by cmasnaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <sys/signal.h>
# include <sys/wait.h>
# include <paths.h>
# include <stdbool.h>
# include <readline/readline.h>

int	g_stat;

typedef enum in
{
	WORD,
	PIPE,
	R_OUT,
	R_IN,
	HER_DOC,
	D_Q,
	S_Q,
	SPACE_,
	VARIABLE,
	APPEND,
}	t_type;

typedef struct s_list
{
	char			*value;
	t_type			type;
	bool			skip;
	struct s_list	*next;	
}	t_list;

typedef struct s_var
{
	int				f_out;
	int				f_in;
	char			**arg;
	struct s_var	*next;	
}	t_var;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*env;
	char	*path;
	char	*shlvl;
	char	*pwd;
	int		no_pwd;
	char	*home;
	int		no_env;
	int		or_in;
	int		status;
	int		status2;
	pid_t	pid;
	int		pipe_ends[2];
	int		len;
	int		val;
}	t_data;

typedef struct s_coll
{
	void			*ptr;
	struct s_coll	*next;
}	t_coll;

//-----------------------LIBFT---------------------

char		*ft_substr(const char *str, unsigned int start, size_t len);;
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(char *str1, char *str2);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *str);
char		*ft_strchr(char *s1, int chr);
void		*ft_memcpy(void *dest1, const void *src1, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *str1, char sep);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_lstadd_back(t_list **lst, t_list *new1);
void		ft_lstclear(t_list **lst);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
int			ft_isalpha(int c);
char		*ft_strtrim(char *str, char set);
void		ft_putstr_fd(char *s, int fd);
void		ft_varadd_back(t_var **lst, t_var *new1);
int			ft_varsize(t_var *lst);
char		*ft_itoa(int n1);
int			ft_lstsize_env(t_env *env);
t_coll		*ft_collnew(void *ptr);
t_coll		*ft_colllast(t_coll **head);
void		ft_colladd_back(t_coll **head, t_coll *new1);
void		ft_collclear(t_coll **head);
void		*c_malloc(size_t size, int flag);

//-----------------------TOKEN---------------------

int			ft_check(char c);
int			ft_token(char *line, t_list *node, t_list **list);
void		ft_skip_space(t_list **list);

//---------------------OPEN_FILES---------------------

int			ft_open_files(t_list **list, t_var *exec, t_data *data);
void		ft_open_her_doc(t_list **list, t_var *exec, t_data *data);

//---------------------EXPAND---------------------

void		ft_expand(t_list **list, t_data *data);
char		*ft_search_var(char *str, t_data *data);
char		*ft_expand_her_doc(char *str, t_data *data);

// ---------------------CREATE_NEW_LIST---------------------

t_var		*ft_allocate_list(t_list **list);
t_var		*ft_varnew(void *value);
void		ft_len_node_elem(t_list **list, t_var *exec);
char		*ft_varjoin(t_list **tmp, t_data *data);
void		ft_copy_to_list(t_list **list, t_var *exec, t_data *data);

//---------------------SYNTAX_ERROR---------------------

int			ft_syntax_error(t_list **list);
int			ft_type(t_list *lst);
t_list		*ft_next(t_list *tmp);

//---------------------EXECUTION---------------------

void		ft_execution(t_var *exec, t_data *data, t_env *env);
void		ft_execute_pipe(t_var *exec, t_data *data, t_env *env);
char		**get_paths(char *path);
char		**get_args(t_var *exec);
void		ft_close_pipe(t_data *data);
char		*valid_path(char *cmd, char *line);
int			check_builtin(t_var *exec, t_data *data);
char		**ft_cpy_to_2d(t_env *tmp);
char		**arg_join(char **args, char **arg);
char		*get_path(t_data *data, char *cmd);

//-----------------------UTILS---------------------

int			exit_status(int new_stat, int set);
void		ft_error(char *str2, char *str3);

//---------------------BUILTS_IN---------------------

void		ft_pwd(t_var *exec, t_env *env, t_data *data);
void		ft_env(t_var *exec, t_data *data);
void		ft_cd(char *path, t_data *data);
void		ft_echo(char **arg, t_var *exec);
void		ft_export(t_var *exec, t_data *data, char **args);
void		ft_unset(t_data **data, char **args);
void		ft_exit(t_var *exec, char **arg, int len);

//------------------BUILTS_IN_UTILS--------------------

char		*ft_var_name(char *line);
char		*ft_remove_plus(char *line);
int			ft_valid_char(char c);
int			ft_arglen(char **arg);
char		*ft_gethome(char *pwd);
long long	ft_valid_arg(char *str, int *valid);
void		ft_print_export(t_var *exec, t_data *data, t_env *env);
void		ft_error_export(char *line, t_data *data);
void		ft_put_line(t_var *exec, char *var, char *name);

//---------------------SIGNALS---------------------

void		ft_signal(void);
void		ft_signal_c(int num);
void		ft_signal_q(int num);
void		ft_signal_her(int num);

//---------------------ENVIRONMENT---------------------

t_env		*ft_get_env(t_data **data, char **env);
char		*ft_get_line(t_data *data, char *line, int i);
void		ft_lstadd_back_env(t_env **env, t_env *p);
char		*ft_lstfind_env(t_env **env, char *line, char *new_line);
t_env		*ft_sort_env(t_env *env, int (*cmp)(char *, char *));
t_env		*ft_lstlast_env(t_env *env);
t_env		*ft_lstnew_env(char *line);
t_env		*ft_lstcpy_env(t_env *env);

#endif
