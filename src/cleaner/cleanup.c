/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:03:43 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 13:49:27 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	free_str(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	clear_texture(mlx_texture_t **tex)
{
	if (!tex || !*tex)
		return ;
	mlx_delete_texture(*tex);
	*tex = NULL;
}

static void	clear_bonus_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < DOOR_FRAME)
	{
		clear_texture(&game->tex.door[i]);
		i++;
	}
	i = 0;
	while (i < SP_FRAME)
	{
		clear_texture(&game->tex.sprite[i]);
		i++;
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->mlx && game->tex.img)
	{
		mlx_delete_image(game->mlx, game->tex.img);
		game->tex.img = NULL;
	}
	clear_texture(&game->tex.north);
	clear_texture(&game->tex.south);
	clear_texture(&game->tex.west);
	clear_texture(&game->tex.east);
	clear_bonus_textures(game);
	free_str(game->map);
	game->map = NULL;
	if (game->mlx)
		mlx_terminate(game->mlx);
}
