NAME = minishell

CC = cc -g -fsanitize=address

# FLAGS = -Wall -Werror -Wextra  

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

OBJ = main.o libft.o tokenizer.o syntax_error.o expand.o open_file.o

all : $(NAME) 

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -L $(READLINE_L) -o  $(NAME) -lreadline

%.o : %.c minishell.h 
	$(CC) -o $@ -c -I $(READLINE_I) $(FLAGS) $< 

clean :
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all 

