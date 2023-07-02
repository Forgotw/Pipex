# PROJET #
NAME = pipex

# HEADER #
INCLUDES = includes/
HEADER_SRCS = pipex.h
HEADER = $(addprefix $(INCLUDES), $(HEADER_SRCS))

# SOURCES #
SRCS = main.c parsing.c free.c error.c child.c heredoc.c
LIBFT_DIR = libft/
LIBFT_FUNC = ft_split.c ft_strdup.c ft_strjoin.c ft_strncmp.c ft_strlen.c get_next_line.c ft_calloc.c ft_bzero.c ft_strchr.c
LIBFT_SRCS = $(addprefix $(LIBFT_DIR), $(LIBFT_FUNC))
OBJS = $(SRCS:.c=.o)
LIBFT_OBJS = $(LIBFT_SRCS:.c=.o)

# UTILS #
CC = gcc
CFLAGS = -Wall -Werror -Wextral
#CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3
RM = rm -rf

# COLORS #
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m

# COMMANDS #
%.o: %.c
				@$(CC) $(FLAGS) -I $(INCLUDES) -c $< -o $@


$(NAME): $(OBJS) $(LIBFT_OBJS)
				@$(CC) $(FLAGS) -I $(INCLUDES) $(OBJS) $(LIBFT_OBJS) -o $(NAME)
				@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"


all: $(NAME)

clean:
				@$(RM) $(OBJS)
				@$(RM) $(LIBFT_OBJS)
				@echo "$(YELLOW)object files cleaned!$(DEFAULT)"

fclean: clean
				@$(RM) $(NAME)
				@echo "$(RED)$(NAME) cleaned!$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean re

