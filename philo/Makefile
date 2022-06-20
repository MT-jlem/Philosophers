NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = philo.c check_arg.c ft_atoi.c ft_strcmp.c utils.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	-rm *.o 

fclean: clean 
	-rm $(NAME)

re: fclean all