# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/17 12:54:11 by wintoo            #+#    #+#              #
#    Updated: 2026/06/16 14:47:16 by wintoo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CC 		= cc
CFlags 	= -Wall -Wextra -Werror -g3

SRC		= src/main.c \
		src/cleaner/cleanup.c \
		src/parser/extract_file.c \
		src/parser/map_utils.c \
		src/parser/parse_color_utils.c \
		src/parser/parse_color.c \
		src/parser/parse_map_utils.c \
		src/parser/parse_map.c \
		src/parser/parse_texture.c \
		src/parser/validate_map.c \
		src/parser/validate_utils.c \
		src/render/run_game.c \
		src/render/third_view.c \
	  	src/render/raycasting.c \
	  	src/render/movement.c \
	  	src/render/texture.c \

BONUS	= src/bonus/scene.c \
		  src/bonus/collision.c \
		  src/bonus/mouse_rot.c \
		  src/bonus/minimap.c \
		  src/bonus/minimap_utils.c \
		  src/bonus/sprite_draw_utils.c \
		  src/bonus/sprite_draw.c \
		  src/bonus/sprite_respawn.c \
		  src/bonus/sprite_anim.c \
		  src/bonus/door.c \
		  src/bonus/door_anim.c

SRCS	= $(SRC) $(BONUS)

OBJS	= $(SRCS:.c=.o)

mlxlib 	= mlxlib/build/libmlx42.a -ldl -lglfw -pthread -lm

RM		= rm -rf

all: MLXLIB $(NAME)

MLXLIB:
		@cmake mlxlib -B mlxlib/build && make -C mlxlib/build -j4
	
$(NAME): $(OBJS)
	$(CC) $(CFlags) $(OBJS) $(mlxlib) ./libft/libft.a -o $@

%.o: %.c
	$(CC) $(CCFlags) -c $< -o $@

clean:
	$(RM) $(OBJS) mlxlib/build

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re