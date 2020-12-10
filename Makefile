NAME		= miniRT.out
SRC			= main.c vec.c color.c key.c sphere.c math_utils.c ray.c draw.c \
			  light.c plane.c objects.c triangle.c camera.c \
			  parser.c parser_utils.c parse_value.c parse_objects.c exit.c \
			  gnl/get_next_line.c gnl/get_next_line_utils.c
HEADER		= vec.h color.h key.h minirt.h math_utils.h ray.h light.h \
			  plane.h objects.h triangle.h \
			  parser.h parser_utils.h parse_value.h parse_objects.h exit.h \
			  gnl/get_next_line.h
OBJS		= $(SRC:.c=.o)
LIBXDIR		= minilibx
LIBXFILE	= libmlx.dylib
LIBXNAME	= mlx
CC			= gcc
#CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

UNAME		:= $(shell uname)

ifeq ($(UNAME),Linux)
	LIBXDIR = minilibx-linux
	LIBXFILE = libmlx.a
	CFLAGS += -D LINUX -L. -lft -l$(LIBXNAME) -L/usr/lib -lX11 -lXext -lm
else
	CFLAGS += -D MACOS -L. -lft -L$(LIBXDIR) -l$(LIBXNAME)

endif	

.PHONY: test all clean fclean re bonus

test:
	$(MAKE) bonus -C libft > /dev/null
	cp libft/libft.a ./
	$(MAKE) -C $(LIBXDIR) > /dev/null
	cp $(LIBXDIR)/$(LIBXFILE) ./
	gcc $(SRC) $(CFLAGS) -g3 -fsanitize=address && ./a.out
	
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBXDIR)
	cp $(LIBXDIR)/$(LIBXFILE) ./
	gcc $(SRC) -L$(LIBXDIR) -l$(LIBXNAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

