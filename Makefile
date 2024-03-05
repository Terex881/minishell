NAME = minishell

CC = cc #-g -fsanitize=address

# FLAGS = -Wall -Werror -Wextra  

OBJ = minishell.o libft.o

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lreadline

%.o : %.c minishell.h
	$(CC) -o $@ -c  $(FLAGS) $< 

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re :
	fclean all
