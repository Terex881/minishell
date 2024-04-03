
NAME = minishell
OBJ = main.o                        syntax_error.o expand.o \
    allocate_list.o         open_files.o \
    libft/ft_isalpha.o        \
    libft/ft_strlen.o       libft/ft_memcpy.o \
    libft/ft_strchr.o       libft/ft_split.o   \
    libft/ft_strcmp.o       libft/ft_lstadd_back.o \
    libft/ft_strdup.o       libft/ft_substr.o   \
    libft/ft_strjoin.o      libft/ft_strtrim.o   \
    libft/ft_lstnew.o       libft/ft_lstadd_front.o  \
    libft/ft_lstdelone.o    libft/ft_putstr_fd.o      \
    libft/ft_lstclear.o     libft/ft_lstiter.o      libft/ft_lstsize.o \
    libft/ft_lstlast.o      libft/ft_strncmp.o      \
    builtins.o              environment.o           execution.o\
    echo.o                  exit.o                  export.o\
    execution_pipe.o        export_utils.o\
    tokenizer/token.o  tokenizer/token_utils.o signals.o \
    env.o                   cd.o                    unset.o\
    pwd.o\

CC = cc -g -fsanitize=address
# FLAGS = -Wall -Werror -Wextra

READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_SRCS)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME) $(READLINE_LIB)
#$(CC) $(OBJ) $(FLAGS) -o $(NAME)

%.o: %.c minishell.h Makefile
	$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@
#$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
