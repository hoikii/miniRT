NAME		= miniRT
INCLUDES	= includes
SRCDIR		= srcs/
SRC			= main.c \
			  vec.c \
			  vec2.c \
			  vec3.c \
			  color.c \
			  key.c \
			  key2.c \
			  mouse.c \
			  objects/sphere.c \
			  objects/plane.c \
			  objects/triangle.c \
			  objects/square.c \
			  objects/cylinder.c \
			  objects/cube.c \
			  objects/pyramid.c \
			  math_utils.c \
			  ray.c \
			  trace_ray.c \
			  render.c \
			  light.c \
			  objects.c \
			  camera.c \
			  parser/parser.c \
			  parser/parser_utils.c \
			  parser/parse_value.c \
			  parser/parse_objects.c \
			  parser/parse_info.c \
			  parser/parse_compounds.c \
			  parser/parse_bonus.c \
			  parser/get_next_line.c \
			  parser/get_next_line_utils.c \
			  hit.c \
			  hit_compounds.c \
			  hit_utils.c \
			  exit.c \
			  disruption.c \
			  checkerboard.c \
			  supersample.c \
			  uv_mapping.c \
			  bmp.c \
			  transform.c \
			  progress.c \
			  show_transform_info.c \
			  color_filter.c
HEADER		= vec.h color.h key.h minirt.h math_utils.h ray.h light.h \
			  plane.h objects.h triangle.h \
			  parser.h parser_utils.h parse_value.h parse_objects.h parse_info.h exit.h \
			  gnl/get_next_line.h trace_ray.h \
			  transform.h hit.h hit_utils.h progress.h
SRCS		= $(addprefix $(SRCDIR), $(SRC))
OBJS		= $(SRCS:.c=.o)
LIBFTDIR	= libft
LIBFTNAME	= ft
CC			= gcc
####################################
####################################
CFLAGS		= -Wall -Wextra
CFLAGS		= -Wall -Wextra -Werror -I $(INCLUDES)
####################################
####################################
RM			= rm -rf

CCBLUE		= \033[34m
CCBLUE_BOLD	= \033[1;34m
CCEND		= \033[0m

UNAME		:= $(shell uname)
ifeq ($(UNAME),Linux)
	CFLAGS		+= -D LINUX
	LIBXDIR		= minilibx-linux
	LIBXFILE	= libmlx.a
	LIBXNAME	= mlx
	LDLIBS		= -L$(LIBFTDIR) -l$(LIBFTNAME) -L$(LIBXDIR) -l$(LIBXNAME)
	LDLIBS		+= -L/usr/lib -lm -lXext -lX11 -lpthread
#	CFLAGS		+= -D THREADS_CNT=$(shell grep -c processor /proc/cpuinfo)
else
	CFLAGS		+= -D MACOS
	LIBXDIR		= minilibx
	LIBXFILE	= libmlx.dylib
	LIBXNAME	= mlx
	LDLIBS		= -L$(LIBFTDIR) -l$(LIBFTNAME) -L$(LIBXDIR) -l$(LIBXNAME)
#	CFLAGS		+= -D THREADS_CNT=$(shell sysctl -n hw.ncpu)
endif

.PHONY: test all bonus cleanlib clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(CCBLUE) >>> make libft with bonus <<< $(CCEND)"
	@$(MAKE) bonus -C libft
	@echo "$(CCBLUE) >>> make minilibx (warning suppressed) <<< $(CCEND)"
	@$(MAKE) -C $(LIBXDIR) 2> /dev/null
	cp $(LIBXDIR)/$(LIBXFILE) ./
	@echo "$(CCBLUE) >>> linking obj files.  <<< $(CCEND)"
	$(CC) $(OBJS) $(CFLAGS) $(LDLIBS) -o $(NAME)
	@echo "$(CCBLUE_BOLD) >>> make $(NAME) done!  <<< $(CCEND)"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: CFLAGS += -DBONUS -D THREADS_CNT=$(shell getconf _NPROCESSORS_ONLN)
bonus: clean all

test: CFLAGS += -g3 -fsanitize=address
test: bonus
	./$(NAME) scenes/smpl.rt

cleanlib:
	@echo "$(CCBLUE) >>> clean libft <<< $(CCEND)"
	$(MAKE) -C $(LIBFTDIR) fclean
	@echo "$(CCBLUE) >>> clean minilibx. <<< $(CCEND)"
	$(MAKE) -C $(LIBXDIR) clean

clean:
	@echo "$(CCBLUE) >>> clean main projects object files. <<< $(CCEND)"
	$(RM) $(OBJS)

fclean: cleanlib clean
	@echo "$(CCBLUE) >>> clean minilibx library file <<< $(CCEND)"
	$(RM) $(LIBXFILE)
	@echo "$(CCBLUE) >>> clean main project's executable. <<< $(CCEND)"
	$(RM) $(NAME)

re: fclean all

