# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 18:22:26 by rbonneva          #+#    #+#              #
#    Updated: 2023/01/23 20:01:58 by rbonneva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY:			all clean fclean re cleanlib fcleanlib

#***********************************************************************#
#								FILES									#
#***********************************************************************#

NAME =			mini_shell
CC =			gcc
CC_FLAGS =		-Wall -Wextra -Werror -fsanitize=address -g3
LIBS =			-L ./Lib_FT \
				-L ./Lib_List_Double
ADDLIBS =		-lft \
				-llstd
LIB_INCS =		-I ./Lib_FT/incs/ \
				-I ./Lib_List_Double/incs/
PATH_OBJ =		./Mini_Shell_Files/objs/
PATH_SRC =		./Mini_Shell_Files/srcs/
PATH_INC =		./Mini_Shell_Files/incs/

FILES_INC =		$(addprefix $(PATH_INC), $(INC))
FILES =			\
				exit \
				free_struct \
				initialize \
				list_cmd_utils \
				main \
				new_struct

INC =			mini_shell.h

OBJS =			$(addprefix $(PATH_OBJ), $(addsuffix .o, $(FILES)))
SRCS =			$(addprefix $(PATH_SRC), $(addsuffix .c, $(FILES)))

#***********************************************************************#
#								RULES									#
#***********************************************************************#

all:			$(NAME)

$(NAME):		$(PATH_OBJ) $(OBJS)
				@$(MAKE) -C ./Lib_FT
				@echo "\033[1mLIB FT\t\t\tCOMPILED\033[0m"
				@$(MAKE) -C ./Lib_List_Double
				@echo "\033[1mLIB List Double\t\tCOMPILED\033[0m"
				@$(CC) $(CC_FLAGS) $(LIBS) $(OBJS) $(MAIN) -o $(NAME) -I $(PATH_INC) $(LIB_INCS) $(ADDLIBS)
				@echo "\033[1mBINARY\t\t\tCOMPILED\033[0m"

$(PATH_OBJ)%.o:	$(PATH_SRC)%.c $(FILES_INC)
				@printf %b " Compilation de \033[1m$<\033[0m en \033[1m$@\033[0m..."
				@$(CC) $(CC_FLAGS) -o $@ -c $< -I $(PATH_INC)
				@printf "\r"
				@printf "                                                                                                                             \r"

$(PATH_OBJ):
				@mkdir $@

clean:
				@rm -rf $(PATH_OBJ)

cleanlib:
				@$(MAKE) -C ./Lib_FT clean
				@$(MAKE) -C ./Lib_List_Double clean

fcleanlib:
				@$(MAKE) -C ./Lib_FT fclean
				@$(MAKE) -C ./Lib_List_Double fclean

fclean:			clean fcleanlib
				@rm -f $(NAME)

re:				fclean all
