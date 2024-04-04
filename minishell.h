# ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libc.h>
#include <errno.h>//errno
#include <stdlib.h>
// #include <string.h>//strerror
#include <unistd.h>
#include <stdbool.h>
#include <sys/signal.h>
#include <termios.h>

// syscall
// echo $USER << a cat ths important


//  ./ls khdmi b lstat or stat
// fix unset path

// minishell : exit "      4"
// exit
// minishell: exit:        4: numeric argument required


// minishell :$USER_d                       $USER
//  sdemnati
// minishell :

// #define malloc(x) NULL

///////////PROTECTION?/////////

// secure PATH

// 'ls -la |  '

// minishell :$fgd
// minishell :echo :$dfgdfg:

// ls | 
//echo "dsf""fsf"


// minishell :exit 10
// exit

// ls | "" 
// ls > ls | wc

typedef struct s_exit
{
	int exitstat;
	
} t_exit;

typedef enum 
{
	WORD,		//0
	PIPE,		//1
	R_OUT,		//2
	R_IN,		//3
	HER_DOC,	//4
	D_Q,		//5
	S_Q,		//6
	SPACE_,		//7
	VARIABLE,	//8
	APPEND,		//9
}t_type;

typedef struct s_list 
{
	char	*value;
	t_type	type;
	bool skip;
	struct s_list *next;	

}t_list;

typedef struct s_var
{
	int f_out;
	int f_in;
	char **arg;
	struct s_var *next;
	
} t_var;

typedef struct  s_env
{
    char    *line;
    struct s_env *next;
}   t_env;

typedef struct s_data
{
	t_env *env;
	char *path;
	char *old_pwd;
	int stat;
}	t_data;




typedef struct s_var1
{
	int		f_in;
	int		f_out;
	pid_t	cp1;
	int		end[2];
	char	*path;
	char	*tmp1;
	char	**arr;
	char	**cmd_args;
	size_t	len;
	int		pos;
	ssize_t	by;
	char	*str;
	int		index;
	char	*sub_line;
	char	*tmp;
}	t_var1;

struct    termios original_terminos;

//-----------------------LIBFT---------------------

char	*ft_substr(const char *str, unsigned int start, size_t len);;
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *str1, char *str2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
char	*ft_strchr(char *s1, int chr);
void	*ft_memcpy(void *dest1, const void *src1, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *str1, char sep);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new1);
void	ft_lstadd_back(t_list **lst, t_list *new1);
void	ft_lstclear(t_list **lst);
void	ft_lstdelone(t_list **lst);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
int     ft_isalpha(int c);
char	*ft_strtrim(char *str, char set);
void	ft_putstr_fd(char *s, int fd);
void	ft_lstclear_var(t_var **exec); 
void	ft_varadd_back(t_var **lst, t_var *new1);
int	ft_varsize(t_var *lst);



int		counter(int n);
char	*ft_itoa(int n1);


//-----------------------TOKEN---------------------

int		ft_check(char c);
// t_list	*ft_add_special_character(t_list *node, char *c, int *i);
// t_list	*ft_add_douple_single(char *line, int *i, t_list *node);
// t_list	*ft_add_word(char *line, int *i, t_list *node);
int		ft_token(char *line, t_list *node, t_list **list);
int		ft_all(t_list **list, t_env *env, t_data	*data);
void	ft_print(t_list *list);
// t_list *ft_add_var(char *line, int *i, t_list *node);
void ft_skip_space(t_list **list);

//---------------------OPEN_FILES---------------------

int		ft_IN_OUT(t_list *tmp, t_var *exec);
int		ft_open_files(t_list **list, t_var *exec);
void	ft_open_her_doc(t_list **list, t_var *exec, t_data *data);

//---------------------EXPAND---------------------

char	*ft_sub_variable(char *str, int *i);
void	ft_expand(t_list **list, t_data *data);
char	*ft_charjoin(char const *s1, char  s2);
char *ft_expand_her_doc(char *str, t_data *data);

// ---------------------CREATE_NEW_LIST---------------------

void	ft_print_var(t_var *list);
t_var	*ft_allocate_list(t_list **list);
// char	*ft_file_name(t_list *tmp);
t_var	*ft_varnew(void *value);
void	ft_len_node_elem(t_list **list, t_var *exec);
char	*ft_varjoin(t_list **tmp);
void	ft_copy_to_list(t_list **list, t_var *exec);

//---------------------SYNTAX_ERROR---------------------

int		ft_syntax_error(t_list **list);
int		ft_type(t_list *lst);

//---------------------EXECUTION---------------------

void		ft_execution(t_var *exec, t_data *data, t_env *env);
void ft_execute_pipe(t_var *exec, t_data *data, t_env *env);
char	**ft_free(char **p, int i);
char **get_paths(char *path);
char *valid_path(char *cmd, char *line);
int	check_builtin(t_var *exec, t_data *data);

char **ft_cpy_to_2d(t_env *tmp);

//---------------------BUILTS_IN---------------------

int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_pwd(t_var *exec, t_env *env);
void	ft_env(t_var *exec, t_data *data);
void	ft_cd(char *path, t_data *data);
void	ft_echo(char **arg, t_var *exec);
void	ft_export(t_var *exec, t_data *data, char *line);
void	ft_unset(t_var *exec, t_data *data, char *line);
void	ft_exit(t_var *exec, t_data **data, char **arg, int len);

//------------------BUILTS_IN_UTILS--------------------

char	*ft_var_name(char *line);
char	*ft_remove_plus(char *line);
int		ft_valid_char(char c);
void	ft_print_export(t_var *exec, t_env *env);
void	ft_error_export(char *line);

//---------------------SIGNALS---------------------

void	ft_signal();
void ft_signal_c(int num);

//---------------------ENVIRONMENT---------------------
t_env   *ft_get_env(t_data **data, char **env);
char	*ft_get_line(t_data *data, char *line, int i);
void	ft_lstclear_env(t_env **env);
void	ft_lstdelone_env(t_env *env);
void	ft_lstadd_back_env(t_env **env, t_env *p);
char	*ft_lstfind_env(t_env **env, char *line, char *new_line);
t_env	*ft_sort_env(t_env *env, int (*cmp)(char *, char *));
t_env	*ft_lstlast_env(t_env *env);
t_env	*ft_lstnew_env(char *line);
t_env	*ft_lstcpy_env(t_env *env);



t_list	*ft_next(t_list *tmp);
int	ft_lstsize_env(t_env *env);

void ft_close(t_var *exec);
void    ft_error(char *str1, char *str2, char *str3);



#endif

// minishell : "ls" -'l''a' | echo -nnnnnnnnnnnnnnnnn
// -nnnnnnnnnnnnnnnnn

// nminishell : "ls" -'l''a' | echo -n -n
// -nminishell : 




// export myname=othame #should work
// export username+=helloworld #should work
// export user-id=456 #syntax error
// export userid=4-3 #should work
// export fullname="othmanebouchta" #should work && {'}
// export 2full=fat #syntax error {the variable name should start with a character {a-z | A-Z}
// export myname+=bouchta

// #output
// myname=othmanebouchta
// username=helloworld
// userid=4-3
// fullname=othmanebouchta

// #when typing `export` without argument should display the arguments in env in a sorted way and also the argument that is not in env like : [export abcdef] [export new]
// export
// #output {example} and sorted
// declare -x COLORTERM="truecolor"
// declare -x LANG="en_US.UTF-8"
// declare -x LESS="-R"
// declare -x abcdef
// declare -x new



// // minishell :echo k
// // k
// // minishell :echo k > l




// //TO FIX !!!!!!
// //ls > ok | cat
// //leaks
// echo ${USER}
// echo $USER$'USER'"$USER"
// echo    "'$'"
// hi "hello 'world "$USER"   '" "$USER' hello "hello world "'$USER' my world" '" hello $USER"'
// echo "e"'e'"e"'e'$USER'e'"e"'e'
// 'world'"e"'e'"$USER'"'e'"e"'e'
// ""''""''$USER""''""''
// '$USER'
// "'$USERdddddd'"
// "hello"   'world'"e"'e'"$USER'"'e'"e"'e'
// echo $USER'$USER'
// echo "$"
// echo ddd"$USER"
// echo $USER${USER}
// Today at 3:02 AM
// echo "'$'"
// echo "$USER"$"$USER"
// echo '"$ddd     "'
// //env -i ....> ls