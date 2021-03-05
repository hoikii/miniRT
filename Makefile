NAME		= miniRT.out
SRC			= main.c vec.c color.c key.c sphere.c math_utils.c ray.c render.c \
			  light.c plane.c objects.c triangle.c camera.c square.c cylinder.c \
			  parser.c parser_utils.c parse_value.c parse_objects.c parse_info.c exit.c \
			  gnl/get_next_line.c gnl/get_next_line_utils.c bmp.c
HEADER		= vec.h color.h key.h minirt.h math_utils.h ray.h light.h \
			  plane.h objects.h triangle.h \
			  parser.h parser_utils.h parse_value.h parse_objects.h parse_info.h exit.h \
			  gnl/get_next_line.h
OBJS		= $(SRC:.c=.o)
LIBXDIR		= minilibx
LIBXFILE	= libmlx.dylib
LIBXNAME	= mlx
LIBFTDIR	= libft
CC			= gcc
#CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

UNAME		:= $(shell uname)

ifeq ($(UNAME),Linux)
	LIBXDIR = minilibx-linux
	LIBXFILE = libmlx.a
	CFLAGS += -D LINUX
	LIBS = -L. -lft -l$(LIBXNAME) -L/usr/lib -lm -lXext -lX11 -lpthread
#	CFLAGS += -D THREADS_CNT=$(shell grep -c processor /proc/cpuinfo)
else
	CFLAGS += -D MACOS
	LIBS = -L. -lft -L$(LIBXDIR) -l$(LIBXNAME)
#	CFLAGS += -D THREADS_CNT=$(shell sysctl -n hw.ncpu)
endif
CFLAGS += -D THREADS_CNT=$(shell getconf _NPROCESSORS_ONLN)




.PHONY: test all clean fclean re bonus

test:
	$(MAKE) bonus -C libft > /dev/null
	cp libft/libft.a ./
	$(MAKE) -C $(LIBXDIR) > /dev/null
	cp $(LIBXDIR)/$(LIBXFILE) ./
	gcc $(SRC) $(CFLAGS) -L$(LIBXDIR) -l$(LIBXNAME) -g3 -fsanitize=address -D BONUS && ./a.out
	
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) bonus -C libft > /dev/null
	cp libft/libft.a ./
	$(MAKE) -C $(LIBXDIR) > /dev/null
	cp $(LIBXDIR)/$(LIBXFILE) ./
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: CFLAGS += -DBONUS
bonus: clean all

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

