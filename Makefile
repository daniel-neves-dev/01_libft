NAME = libft.a
SRCS = ft_bzero.c
FLAGS = gcc -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	@$(FLAGS) $(SRCS)
	@./a.out

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)

re:	fclean all
