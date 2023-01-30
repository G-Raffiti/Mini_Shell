.PHONY:			all clean fclean re cleanlib fcleanlib

#***********************************************************************#
#								FILES									#
#***********************************************************************#

NAME =			mini_shell
CC =			gcc
CC_FLAGS =		-Wall -Wextra -Werror -fsanitize=address -g3

PATH_OBJ =		./Mini_Shell_Files/objs/
PATH_SRC =		./Mini_Shell_Files/srcs/
PATH_INC =		./Mini_Shell_Files/incs/

LINK_LIB =		-L ./Lib_FT \
				-L ./Lib_List_Double
ADD_LIB =		-lft \
				-llstd
INC_LIB =		-I ./Lib_FT/incs/ \
				-I ./Lib_List_Double/incs/
FILE_LIB =		./Lib_FT/incs/libft.h \
				./Lib_List_Double/incs/ft_lstd.h

FILES =			\
				debug \
				env \
				exit \
				free_struct \
				list_cmd_utils \
				main \
				new_struct \
				parsing \
				parsing_chevron \
				parsing_get_cmd \
				parsing_get_raw_cmd \
				read_line \
				safe_fuctions

INC =			mini_shell.h

FILES_INC =		$(addprefix $(PATH_INC), $(INC))
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
				@$(CC) $(CC_FLAGS) $(LINK_LIB) $(OBJS) $(MAIN) -o $(NAME) -I $(PATH_INC) $(INC_LIB) $(ADD_LIB)
				@echo "\033[1mBINARY\t\t\tCOMPILED\033[0m"

$(PATH_OBJ)%.o:	$(PATH_SRC)%.c $(FILES_INC) $(FILE_LIB)
				@printf %b " \033[1m$<\033[0m -> \033[1m$@\033[0m..."
				@$(CC) $(CC_FLAGS) -o $@ -c $< -I $(PATH_INC)
				@printf "\r"
				@printf "                                                                                               \r"

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
