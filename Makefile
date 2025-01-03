CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

LIBDIR = libft
LIB = $(LIBDIR)/libft.a

SRC = init.c main.c map.c map_validation.c path_check.c player.c render.c utils.c

SRCS :=  $(addprefix src/,$(SRC))
OFILES := $(addprefix ofiles/,$(SRC:.c=.o))

NAME = so_long


ofiles/%.o: src/%.c includes/so_long.h | dirs
	$(CC) $(CFLAGS) -c $< -o $@

all: dirs $(NAME)

$(NAME): $(OFILES) $(LIB)
	@$(CC) $(OFILES) -L$(LIBDIR) -lft -lmlx \
	-lXext -lX11 -lm -o $(NAME)

$(LIB):
	make -C $(LIBDIR)

clean:
	rm -rf ofiles
	make clean -C $(LIBDIR)

fclean: clean
	make fclean -C $(LIBDIR)
	rm -rf $(NAME)

re: fclean all

dirs:
	@mkdir -p ofiles

.PHONY: dirs all clean fclean re
