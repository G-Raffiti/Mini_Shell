.PHONY:			all clean fclean re cleanlib fcleanlib

#***********************************************************************#
#								FILES									#
#***********************************************************************#

NAME =			minishell
CC =			gcc
CC_FLAGS =		-Wall -Wextra -Werror -gdwarf-4 -g #-fsanitize=address

PATH_OBJ =		./Mini_Shell_Files/objs/
PATH_SRC =		./Mini_Shell_Files/srcs/
PATH_INC =		./Mini_Shell_Files/incs/

LINK_LIB =		-L ./Lib_FT \
				-L ./Lib_List_Double
ADD_LIB =		-lft \
				-llstd \
				-lreadline
INC_LIB =		-I ./Lib_FT/incs/ \
				-I ./Lib_List_Double/incs/
FILE_LIB =		./Lib_FT/incs/libft.h \
				./Lib_List_Double/incs/ft_lstd.h

FILES =			\
				builtin/builtin \
				builtin/builtin_errors \
				builtin/ft_cd \
				builtin/ft_echo \
				builtin/ft_exit \
				builtin/ft_pwd \
				builtin/ft_export \
				builtin/ft_env \
				builtin/ft_unset \
				\
				debug/debug \
				debug/test_mode \
				\
				env/env \
				env/env_regen \
				env/modif_env \
				\
				exec/exec \
				exec/signals \
				\
				parsing/check_line \
				parsing/chevron \
				parsing/get_cmd \
				parsing/get_path \
				parsing/get_raw_cmd \
				parsing/parsing \
				parsing/read_line \
				parsing/replace_dollars \
				parsing/replace_tilde \
				parsing/set_builtin \
				\
				utils/env_utils \
				utils/env_type_utils \
				utils/dict_utils \
				utils/free_struct \
				utils/list_cmd_utils \
				utils/new_struct \
				utils/safe_functions \
				utils/check_functions \
				\
				exit \
				exit_code \
				main


INC =			mini_shell.h \
				error.h \
				debug.h

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
				@mkdir $(PATH_OBJ)/builtin
				@mkdir $(PATH_OBJ)/debug
				@mkdir $(PATH_OBJ)/env
				@mkdir $(PATH_OBJ)/exec
				@mkdir $(PATH_OBJ)/parsing
				@mkdir $(PATH_OBJ)/utils

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
