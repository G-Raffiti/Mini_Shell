
.PHONY:			all clean fclean re bonus

#***********************************************************************#
#								FILES									#
#***********************************************************************#

NAME =			libft.a
CC =			clang
CC_FLAGS =		-Wall -Wextra -Werror -g3
PATH_OBJ =		./objs/
PATH_SRC =		./srcs/
PATH_INC =		./incs/
INC =			libft.h
FILES_INC =		$(addprefix $(PATH_INC), $(INC))
FILES =			ft_contain \
				ft_bzero \
				ft_putchar_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_putstr_fd \
				ft_striteri \
				ft_tolower \
				ft_toupper \
				ft_atoi \
				ft_isalnum \
				ft_isalpha \
				ft_isascii \
				ft_isdigit \
				ft_isprint \
				ft_memcmp \
				ft_strlcpy \
				ft_strlcat \
				ft_strlen \
				ft_strncmp \
				ft_calloc \
				ft_memchr \
				ft_memcpy \
				ft_memmove \
				ft_memset \
				ft_itoa \
				ft_substr \
				ft_strchr \
				ft_strdup \
				ft_strjoin \
				ft_strmapi \
				ft_strnstr \
				ft_strrchr \
				ft_strtrim \
				ft_split\
				ft_strlen_tab
OBJS =			$(addprefix $(PATH_OBJ), $(addsuffix .o, $(FILES)))
BONUSOBJS =		$(addprefix $(PATH_OBJ), $(addsuffix .o, $(BONUSES)))
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

fclean: clean
				@rm -rf $(NAME)

re:				fclean
				all
