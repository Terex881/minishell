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




//////////////////////////////////PROTECTION?/////////


typedef enum 
{
	WORD,           // 0   
	PIPE,           // 1
	R_OUT,          // 2 
	R_IN,           // 3
	HER_DOC,        // 4
	D_Q,            // 5
	S_Q,            // 6
	SPACE_,         // 7
	VARIABLE,       // 8
	APPEND,         // 9
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

char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strrchr(const char *s, int chr);
char	*ft_strnstr(const char *s1, const char *s2, size_t size);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *s, int chr);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memmove(void *str1, const void *str2, size_t n);
void	*ft_memcpy(void *dest1, const void *src1, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
int		ft_atoi(const char *str);
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
char	*ft_strtrim(char const *str, char const *set);
void	ft_putstr_fd(char *s, int fd);

int		ft_check(char c);
t_list	*ft_add_special_character(t_list *node, char *c, int *i);
t_list	*ft_add_word(char *line, int *i, t_list *node);
void	ft_token(t_list **list);
void	ft_print(t_list *list);

void	ft_syntax_error(t_list **list);
int     ft_return(t_list *lst);

void    ft_expand(t_list *list);
char    *ft_get_variable(char *str, int *i);

void	ft_open_files(t_list **list, t_var *exec);
t_var	*ft_new(void *value);

t_var	*ft_sakawi(void *value);
void	ft_lstadd_var(t_var **lst, t_var *new1);
int		ft_size(t_var *lst); // remove



t_var	*ft_get_number_of_pipe(t_list **list);
void	ft_lstadd_var(t_var **lst, t_var *new1);
char	*ft_name_of_file(t_list *tmp);
t_var	*ft_allocate_for_new_node(void *value);
void	ft_print_var(t_var *list);



void ft_call(t_list **list, t_var *var);


#endif

