.PHONY:			all clean fclean re cleanlib fcleanlib force

#***********************************************************************#
#								FILES									#
#***********************************************************************#

NAME =			minishell
CC =			gcc
CC_FLAGS =		-Wall -Wextra -Werror -gdwarf-4 -g3 #-fsanitize=address

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
LIB_A =			./Lib_FT/libft.a \
				./Lib_List_Double/liblstd.a

FILES =			\
				builtin/builtin \
				builtin/ft_cd \
				builtin/ft_echo \
				builtin/ft_exit \
				builtin/ft_pwd \
				builtin/ft_export \
				builtin/ft_env \
				builtin/ft_unset \
				\
				env/env \
				env/env_regen \
				env/modif_env \
				\
				exec/exec \
				exec/exec_error \
				exec/exec_pipeline \
				exec/exec_utils \
				exec/here_docs \
				exec/signals_handler \
				exec/signals_seter \
				exec/here_docs_expand \
				exec/here_docs_expand_replace \
				exec/here_docs_expand_utils \
				\
				parsing/check_line \
				parsing/chevron \
				parsing/file_extract_file_name \
				parsing/get_cmd \
				parsing/get_cmd_str_dup \
				parsing/get_path \
				parsing/get_raw_cmd \
				parsing/inv_quote \
				parsing/open_file \
				parsing/parse_error \
				parsing/parsing \
				parsing/read_line \
				parsing/replace_dollars_check_special \
				parsing/replace_dollars_final_line \
				parsing/replace_dollars_split \
				parsing/replace_tilde \
				parsing/replace_tilde_split \
				parsing/set_builtin \
				\
				utils/check_functions \
				utils/close_all_files \
				utils/dict_utils \
				utils/env_type_utils \
				utils/env_utils \
				utils/free_struct \
				utils/ft_free \
				utils/list_cmd_utils \
				utils/new_struct \
				utils/safe_functions \
				\
				exit \
				end_child \
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

$(LIB_A):		force
				$(MAKE) -C ./Lib_FT
				$(MAKE) -C ./Lib_List_Double

$(NAME):		$(PATH_OBJ) $(OBJS)
				$(CC) $(CC_FLAGS) $(LINK_LIB) $(OBJS) $(MAIN) -o $(NAME) -I $(PATH_INC) $(INC_LIB) $(ADD_LIB)

$(PATH_OBJ)%.o:	$(PATH_SRC)%.c $(LIB_A) $(FILES_INC) $(FILE_LIB)
				$(CC) $(CC_FLAGS) -o $@ -c $< -I $(PATH_INC)
				@printf "\r"
				@printf "                                                                                            \r"

$(PATH_OBJ):
				mkdir $@
				mkdir $(PATH_OBJ)/builtin
				mkdir $(PATH_OBJ)/debug
				mkdir $(PATH_OBJ)/env
				mkdir $(PATH_OBJ)/exec
				mkdir $(PATH_OBJ)/parsing
				mkdir $(PATH_OBJ)/utils

clean:
				rm -rf $(PATH_OBJ)

cleanlib:
				$(MAKE) -C ./Lib_FT clean
				$(MAKE) -C ./Lib_List_Double clean

fcleanlib:
				$(MAKE) -C ./Lib_FT fclean
				$(MAKE) -C ./Lib_List_Double fclean

fclean:			clean fcleanlib
				rm -f $(NAME)

re:				fclean all
