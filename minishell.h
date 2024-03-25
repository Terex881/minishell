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
// handl echo -nnnnn  "$USER".$USER
// bash-3.2$ echo '$USER."'$USER'"'$0
// $USER."sdemnati"bash
// bash-3.2$ echo '$USER."'$USER'"'$1
// $USER."sdemnati"

// bash-3.2$ echo '$USER'
// $USER

// minishell :$USER_d                       $USER
//  sdemnati
// minishell :
// minishell :> 
// 22
// [1]    50640 segmentation fault  ./minishell
// #define malloc(x) NULL
///////////PROTECTION?/////////
// remove unused function of libft

// $$$$$$$$$$$$$$$$$$$$6

// minishell :ls > "ls"
// ---->(")

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

char	*ft_substr(const char *str, unsigned int start, size_t len);;
// char	*ft_strnstr(const char *s1, const char *s2, size_t size);
int		ft_strncmp(char *str1, char *str2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
char	*ft_strchr(char *s1, int chr);
// void	*ft_memset(void *b, int c, size_t len);
// void	*ft_memmove(void *str1, const void *str2, size_t n);
void	*ft_memcpy(void *dest1, const void *src1, size_t n);
// int		ft_memcmp(const void *str1, const void *str2, size_t n);
// int		ft_atoi(const char *str);
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
void	ft_token(t_list **list);
void	ft_print(t_list *list);

//---------------------OPEN_FILES---------------------

void	ft_IN_OUT(t_list *tmp, t_var *exec);
void	ft_open_files(t_list **list, t_var *exec);
void	ft_open_her_doc(t_list **list, t_var *exec);
void	ft_full_list(t_list **list, t_var *exec);
void	ft_call(t_list **list, t_var *exec);

//---------------------EXPAND---------------------

char	*ft_get_variable(char *str, int *i);
void	ft_expand(t_list *list);

// ---------------------CREAtE_NEW_LIST---------------------

void	ft_print_var(t_var *list);
t_var	*ft_allocate_list(t_list **list);
char	*ft_file_name(t_list *tmp);
t_var	*ft_varnew(void *value);
void	ft_len_node_elem(t_list **list, t_var *exec);

//---------------------SYNTAX_ERROR---------------------

int		ft_return(t_list *lst);
void	ft_syntax_error(t_list **list);



#endif

