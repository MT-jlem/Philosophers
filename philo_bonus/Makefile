NAME = philo_bonus

CC = cc 

CFLAGS = -Wall -Wextra -Werror -pthread

SRC = philo_bonus.c check_arg_bonus.c ft_atoi.c ft_strcmp.c utils.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	-rm *.o 

fclean: clean 
	-rm philo_bonus

re: fclean all