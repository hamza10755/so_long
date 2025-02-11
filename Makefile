NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes -g

SRC = src
LIBFTDIR = libft

SRCS = main.c \
       init.c \
       map_validation.c \
       map.c \
       path_check.c \
       player.c \
       render.c \
       utils.c

SRC_FILES = $(addprefix $(SRC)/, $(SRCS))
OFILES = $(SRCS:.c=.o)

LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

%.o: $(SRC)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OFILES) $(LIBFT)
	@$(CC) $(OFILES) -L$(LIBFTDIR) -lft -lmlx -lXext -lX11 -lm -o $(NAME)

$(LIBFT):
	@make -C $(LIBFTDIR)

clean:
	@rm -f $(OFILES)
	@make -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean