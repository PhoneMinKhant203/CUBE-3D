/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:26:24 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 14:34:22 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include "mlxlib/include/MLX42/MLX42.h"
# include "libft/libft.h"

// game constants
# define G_WIDTH 1920
# define G_HEIGHT 1280

// map parsing
# define CFG_NO 1
# define CFG_SO 2
# define CFG_WE 4
# define CFG_EA 8
# define CFG_F 16
# define CFG_C 32
# define CFG_ALL 63

// movement constants
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0
# define MOUSE_SENSITIVITY 0.0025
# define PLAYER_RADIUS 0.40

// minimap constants
# define MINI_SCALE 20
# define MINI_MARGIN 10
# define MINI_WIDTH 20
# define MINI_HEIGHT 14
# define MINI_BG 0x00000099
# define MINI_WALL 0x222222FF
# define MINI_FLOOR 0xDDDDDDFF
# define MINI_DOOR 0x8B4513FF
# define MINI_PLAYER 0xFF0000FF
# define MINI_DIR 0x87CEEB99
# define RADAR_LEN 35
# define RADAR_WIDTH 0.45

// door constants
# define DOOR_CLOSE 'D'
# define DOOR_OPEN 'O'
# define DOOR_FRAME 4
# define DOOR_ANIM_SPEED 0.25
# define DOOR_AUTO_TIMER 6.0

// sprite constants
# define SP_COUNT 4
# define SP_FRAME 2
# define SP_DIST 3.0
# define SP_REACH 0.15
# define SP_ANIM_SPEED 0.3

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_dx;
	double	side_dy;
	double	delta_dx;
	double	delta_dy;
	double	perp_wall_dt;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	char	side;
	char	hit;
}	t_ray;

typedef struct s_texline
{
	mlx_texture_t	*tex;
	int				start;
	int				end;
	double			step;
	double			pos;
}	t_texline;

typedef struct s_texture
{
	mlx_image_t		*img;
	uint32_t		floor;
	uint32_t		ceiling;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_texture_t	*door[DOOR_FRAME];
	mlx_texture_t	*sprite[SP_FRAME];
}	t_texture;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	target_x;
	double	target_y;
	double	dist;
	double	speed;
	double	delay;
	double	timer;
	int		frame;
	int		isactive;
}	t_sprite;

typedef struct s_spdraw
{
	mlx_texture_t	*tex;
	double			trans_y;
	int				screen_x;
	int				width;
	int				height;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
	int				origin_x;
	int				origin_y;
}	t_spdraw;

typedef enum e_door_state
{
	CLOSED,
	CLOSING,
	OPEN,
	OPENING
}	t_door_state;

typedef struct s_door
{
	int				x;
	int				y;
	int				frame;
	int				dir;
	int				active;
	double			anim_timer;
	double			open_time;
}	t_door;

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	int				mouse_lock;
	int				mouse_toggle;
	int				door_toggle;
	double			z_buffer[G_WIDTH];
	uint32_t		rng;
	t_texture		tex;
	t_player		player;
	t_door			door;
	t_sprite		sprites[SP_COUNT];
}	t_game;

// cleanup
void			free_str(char **arr);
void			cleanup_game(t_game *game);

// map parsing
int				init_game(t_game *game, char *filename);
int				get_map_height(t_game *game);
void			set_map_cell(t_game *game, int x, int y, char value);
char			get_map_cell(t_game *game, int x, int y);
int				get_map_width(t_game *game);
int				is_cub_file(char *filename);
char			**extract_file(char *filename);
int				is_cub_file(char *filename);
int				parse_cub(t_game *game, char *filename);
int				parse_texture(t_game *game, char *line, int *mask);
int				parse_color(t_game *game, char *line, int *mask);
int				parse_map(t_game *game, char **lines, int start);
int				validate_map(t_game *game);
int				skip_spaces(char *line, int i);
int				parse_num(char *line, int *i, int *num);
uint32_t		to_rgba(int rgb[3]);
int				is_empty_line(char *line);
int				is_map_start(char *line);
int				count_map_lines(char **lines, int start);
int				copy_map_line(t_game *game, char **lines, int start, int i);
int				is_player(char c);
int				is_walkable(char c);
void			set_player(t_game *game, int x, int y, char c);

// collision and movement
int				is_collision(t_game *game, double x, double y);
int				is_wall(t_game *game, int x, int y);
void			rotate_player(t_game *game, double ang);
void			move_player(t_game *game);

// bonus
int				init_bonus(t_game *game);
void			handle_mouse_toggle(t_game *game);
void			handle_mouse_rotation(t_game *game);
void			init_door_anim(t_game *game, int x, int y);
void			stop_door_anim(t_game *game);
void			update_auto_close(t_game *game);
void			update_door(t_game *game);
void			put_pixel(t_game *game, int x, int y, uint32_t color);
void			draw_square(t_game *game, int x, int y, uint32_t color);
void			draw_minimap(t_game *game);
uint32_t		next_rng(t_game *game);
void			sort_sprites(t_game *game);
void			draw_sprite_col(t_game *game, t_spdraw *d, int stripe);
void			respawn_sprite(t_game *game, t_sprite *sp);
void			update_sprites(t_game *game);
void			draw_sprites(t_game *game);

// render scene
uint32_t		get_tex_color(mlx_texture_t *tex, int tex_x, int tex_y);
mlx_texture_t	*get_tex(t_game *game, t_ray *ray);
int				get_tex_x(t_game *game, t_ray *ray);
void			draw_wall(t_game *game, t_ray *ray, int x);
void			draw_background(t_game *game);
void			raycast(t_game *game);
void			render(void *param);

#endif