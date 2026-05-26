NAME = libft.a
SRCS = ft_atoi.c
FLAGS = gcc -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	@$(FLAGS) $(SRCS)
	@./a.out

clean:
	rm -f $(OBJS)
	rm -f ./a.out
fclean: clean
	rm -f $(NAME)
re:	fclean
