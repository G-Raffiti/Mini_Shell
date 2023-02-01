
.PHONY:			all clean fclean re bonus

#***********************************************************************#
#								FILES									#
#***********************************************************************#

NAME =			liblstd.a
CC =			gcc
CC_FLAGS =		-Wall -Wextra -Werror -gdwarf-4 -g3
PATH_OBJ =		./objs/
PATH_INC =		./incs/
PATH_SRC =		./srcs/

FILES_INC =		./incs/ft_lstd.h

FILES =			ft_lstd_at \
				ft_lstd_clear \
				ft_lstd_contain \
				ft_lstd_del \
				ft_lstd_find \
				ft_lstd_first \
				ft_lstd_foreach \
				ft_lstd_foreach_if \
				ft_lstd_insert \
				ft_lstd_last \
				ft_lstd_merge \
				ft_lstd_move \
				ft_lstd_new \
				ft_lstd_push_back \
				ft_lstd_push_front \
				ft_lstd_push_tab \
				ft_lstd_remove \
				ft_lstd_remove_if \
				ft_lstd_reverse \
				ft_lstd_size \
				ft_lstd_sort

OBJS =			$(addprefix $(PATH_OBJ), $(addsuffix .o, $(FILES)))
SRCS =			$(addprefix $(PATH_SRC), $(addsuffix .c, $(FILES)))

#***********************************************************************#
#								RULES									#
#***********************************************************************#

all:			$(NAME)

$(NAME):		$(PATH_OBJ) $(OBJS)
				@ar rcs $(NAME) $(OBJS)
				@ranlib $(NAME)

$(PATH_OBJ)%.o:	$(PATH_SRC)%.c $(FILES_INC)
				@printf %b " Compilation de \033[1m$<\033[0m en \033[1m$@\033[0m..."
				@$(CC) $(CC_FLAGS) -o $@ -c $< -I $(PATH_INC)
				@printf "\r"
				@printf "                                                                                     \r"

$(PATH_OBJ):
				@mkdir $@

clean:
				@rm -rf $(PATH_OBJ)

fclean:			clean
				@rm -rf $(NAME)

re:				fclean
				all
