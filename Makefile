# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmasnaou <cmasnaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/07 01:30:33 by sdemnati          #+#    #+#              #
#    Updated: 2024/04/11 17:31:24 by cmasnaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
OBJ = main.o				syntax_error.o 			expand.o  \
	allocate_list.o			open_files.o 			coll.o \
	execution.o  			signals.o				tokenizer/token.o \
	utils_execution.o		tokenizer/token_utils.o  \
    libft/ft_isalpha.o      libft/ft_strlen.o       libft/ft_memcpy.o \
    libft/ft_strchr.o       libft/ft_split.o   		libft/ft_strcmp.o \
    libft/ft_lstadd_back.o  libft/ft_strdup.o       libft/ft_substr.o \
    libft/ft_strjoin.o      libft/ft_strtrim.o   	libft/ft_lstnew.o \
	libft/ft_itoa.o 		libft/ft_putstr_fd.o    libft/ft_lstsize.o \
    libft/ft_lstlast.o      libft/ft_strncmp.o  \
    built_in/environment.o  built_in/echo.o         built_in/exit.o \
	built_in/export.o		execution_pipe.o		built_in/export_utils.o \
   	built_in/env.o			built_in/cd.o           built_in/unset.o \
    built_in/pwd.o                    

CC = cc
FLAGS = -Wall -Werror -Wextra
MAGENTA	=	\033[0;35m
CYAN	=	\033[1;92m
YELLOW	=	\033[1;33m
NC		=	\033[0m

READLINE_INC = -I$(shell brew --prefix readline)/include
READLINE_LIB = -L$(shell brew --prefix readline)/lib -lreadline

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_SRCS)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME) $(READLINE_LIB)
	echo "🌸 ${CYAN}Done! 🌸 ${NC}use ${MAGENTA}./minishell 🌸"

%.o: %.c minishell.h Makefile
	$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

clean:
	rm -rf $(OBJ)
	echo "🌸 ${YELLOW}Cleanup done! 🌸"

fclean: clean
	rm -rf $(NAME)

re: fclean all

m: all clean

.PHONY: clean
 
.SILENT: