/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 16:16:12 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 12:08:04 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	load_bonus_tex(mlx_texture_t **img, char **paths, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		img[i] = mlx_load_png(paths[i]);
		if (!img[i])
		{
			ft_putstr_fd("Error\nFailed to load texture: ", 2);
			ft_putendl_fd(paths[i], 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_sprites(t_game *game)
{
	char	*paths[SP_FRAME];
	int		i;

	paths[0] = "./textures/sprites/soul1.png";
	paths[1] = "./textures/sprites/soul2.png";
	if (!load_bonus_tex(game->tex.sprite, paths, SP_FRAME))
		return (0);
	i = 0;
	while (i < SP_COUNT)
	{
		ft_bzero(&game->sprites[i], sizeof(t_sprite));
		game->sprites[i].isactive = 0;
		game->sprites[i].delay = 1.0 + (double)i * 2.0;
		i++;
	}
	return (1);
}

int	init_bonus(t_game *game)
{
	char	*paths[DOOR_FRAME];

	paths[0] = "./textures/door/door1.png";
	paths[1] = "./textures/door/door2.png";
	paths[2] = "./textures/door/door3.png";
	paths[3] = "./textures/door/door4.png";
	if (!load_bonus_tex(game->tex.door, paths, DOOR_FRAME))
		return (0);
	game->mouse_lock = 0;
	game->mouse_toggle = 0;
	game->door_toggle = 0;
	game->rng = 2463534242u;
	if (!init_sprites(game))
		return (0);
	return (1);
}
