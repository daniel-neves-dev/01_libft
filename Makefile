NAME = libft.a
SRCS = $(wildcard ft_*.c)
CC = gcc
FLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)

all:	$(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o:	%.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)
	rm -f ./a.out
fclean: clean
	rm -f $(NAME)
re:	fclean

.PHONY:	re
