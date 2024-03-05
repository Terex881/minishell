# ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libc.h>
#include <stdlib.h>

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
    char *value;
    int     type;
    struct s_list *next;
} t_list;

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
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);
// void	ft_lstiter(t_list *lst, void (*f)(void *));
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);

#endif