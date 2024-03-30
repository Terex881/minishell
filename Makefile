NAME = minishell

CC = cc -g -fsanitize=address

# FLAGS = -Wall -Werror -Wextra  

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

OBJ = main.o                tokenizer.o             syntax_error.o expand.o \
    allocate_list.o         open_files.o \
    libft/ft_isalpha.o      libft/ft_varclear.o     libft/ft_varadd_back.o  \
    libft/ft_strlen.o       libft/ft_memcpy.o \
    libft/ft_strchr.o       libft/ft_split.o   \
    libft/ft_strcmp.o       libft/ft_lstadd_back.o \
    libft/ft_strdup.o       libft/ft_substr.o   \
    libft/ft_strjoin.o      libft/ft_strtrim.o   \
    libft/ft_lstnew.o       libft/ft_lstadd_front.o  \
    libft/ft_lstdelone.o    libft/ft_putstr_fd.o    libft/ft_newvar.o  \
    libft/ft_lstclear.o     libft/ft_lstiter.o      libft/ft_lstsize.o \
    libft/ft_lstlast.o      libft/ft_strncmp.o      execution.o\
    builtins.o              environment.o\

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -L $(READLINE_L) -o  $(NAME) -lreadline
# $(CC) $(OBJ)  -o  $(NAME) -lreadline

# <<<<<<< HEAD
# %.o : %.c minishell.h Makefile
# =======
%.o : %.c minishell.h Makefile # check this
	$(CC) -o $@ -c -I $(READLINE_I) $(FLAGS) $< 
# >>>>>>> 65a30a145e3999c30748e3c2df8a3134faab1b2f
# $(CC) -o $@ -c $(FLAGS) $< 

clean :
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME) 

re: fclean all 
#  .SILENT:
