# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdemnati <sdemnati@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/07 01:30:33 by sdemnati          #+#    #+#              #
#    Updated: 2024/05/09 11:49:05 by sdemnati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJ = main.o				syntax_error.o\
	allocate_list.o			open_files.o\
	tokenizer/token_utils.o tokenizer/token.o  			coll.o \
	signals.o				expand/expand.o  			expand/expand_utils.o  \
    built_in/cd.o 			built_in/echo.o         	built_in/exit.o \
   	built_in/env.o			built_in/env_utils.o        built_in/unset.o\
    built_in/export.o		built_in/export_utils.o		built_in/pwd.o\
	execution/execution.o	execution/execution_utils.o	execution/execution_pipe.o\
	\
    libft/ft_isalpha.o      libft/ft_strlen.o       libft/ft_memcpy.o \
    libft/ft_strchr.o       libft/ft_split.o   		libft/ft_strcmp.o \
    libft/ft_lstadd_back.o  libft/ft_strdup.o       libft/ft_substr.o \
    libft/ft_strjoin.o      libft/ft_strtrim.o   	libft/ft_lstnew.o \
	libft/ft_itoa.o 		libft/ft_putstr_fd.o    libft/ft_lstsize.o \
    libft/ft_lstlast.o      libft/ft_strncmp.o\

CC = cc #-g -fsanitize=address
# FLAGS = -Wall -Werror -Wextra


READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_SRCS)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME) $(READLINE_LIB)

%.o: %.c minishell.h Makefile
	$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

m: all clean


 
.SILENT: