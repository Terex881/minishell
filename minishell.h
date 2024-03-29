# ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libc.h>
#include <stdlib.h>
#include <stdbool.h>
// syscall
//  echo yassi" ne 



// minishell :$USER_d                       $USER
//  sdemnati
// minishell :

// #define malloc(x) NULL

///////////PROTECTION?/////////


// $$$$$$$$$$$$$$$$$$$$6

// minishell :echo {$USER;$USER}
// {sdemnati;sdemnati}



typedef enum 
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

//-----------------------TOKEN---------------------

int		ft_check(char c);
t_list	*ft_add_special_character(t_list *node, char *c, int *i);
t_list	*ft_add_douple_single(char *line, int *i, t_list *node);
t_list	*ft_add_word(char *line, int *i, t_list *node);
int	ft_token(char *line, t_list *node, t_list **list);
void	ft_all(t_list **list, char **env);
void	ft_print(t_list *list);

//---------------------OPEN_FILES---------------------

int		ft_IN_OUT(t_list *tmp, t_var *exec);
int		ft_open_files(t_list **list, t_var *exec);
void	ft_open_her_doc(t_list **list, t_var *exec);

//---------------------EXPAND---------------------

char	*ft_get_variable(char *str, int *i);
void	ft_expand(t_list **list, char **env);
char	*ft_charjoin(char const *s1, char  s2);
char	*ft_expand_her_doc(char *str);

// ---------------------CREATE_NEW_LIST---------------------

void	ft_print_var(t_var *list);
t_var	*ft_allocate_list(t_list **list);
char	*ft_file_name(t_list *tmp);
t_var	*ft_varnew(void *value);
void	ft_len_node_elem(t_list **list, t_var *exec);
char	*ft_varjoin(t_list **tmp);
void	ft_copy_to_list(t_list **list, t_var *exec);

//---------------------SYNTAX_ERROR---------------------

int		ft_syntax_error(t_list **list);
int		ft_type(t_list *lst);

//---------------------EXECUTION---------------------

int		ft_execution(t_var *exec, char **env);

//---------------------BUILTS_IN---------------------

int	ft_strncmp(const char *s1, const char *s2, size_t n);
void ft_echo(char **arg);
void ft_pwd(char *arg);
void ft_env(char **env);
void ft_cd(char *path);


#endif

