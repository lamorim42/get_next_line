SRC = get_next_line.c get_next_line_utils.c
MAIN = main.c
OBJ = $(SRC:.c=.o)
MAIN_OBJ = $(MAIN:.c=.o)
NAME = get_next_line

CC = clang
CCFLAGS = -fsanitize=address -g3 -Wall -Wextra -Werror
GNLFLAGS = -D BUFFER_SIZE=1

RM = rm -f

.c.o:
	$(CC) $(CCFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) $(MAIN) $(SRC)

test:
	$(CC) $(MAIN) $(SRC)

clean:
	$(RM) $(OBJ) $(MAIN_OBJ)

fclean: clean
	$(RM) a.out

run:
	./a.out

gdb: all
	gdb ./a.out

re: fclean all

git:
	git status
	git add .

.PHONY: all clean fclean re
