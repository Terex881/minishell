NAME = minishell

CC = cc -g -fsanitize=address

# FLAGS = -Wall -Werror -Wextra  

OBJ = main.o libft.o tokenizer.o syntax_error.o expand.o open_file.o

all : $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lreadline

%.o : %.c minishell.h
	$(CC) -o $@ -c  $(FLAGS) $< 

clean :
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all 

