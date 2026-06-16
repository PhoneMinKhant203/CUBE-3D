/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:52:53 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 14:35:07 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	init_game(t_game *game, char *filename)
{
	ft_bzero(game, sizeof(t_game));
	if (!parse_cub(game, filename))
		return (0);
	game->mlx = mlx_init(G_WIDTH, G_HEIGHT, "cub3D", false);
	if (!game->mlx)
	{
		ft_putendl_fd("Error\nMLX init failed.", 2);
		return (0);
	}
	game->tex.img = mlx_new_image(game->mlx, G_WIDTH, G_HEIGHT);
	if (!game->tex.img)
	{
		ft_putendl_fd("Error\nImage creation failed.", 2);
		return (0);
	}
	if (mlx_image_to_window(game->mlx, game->tex.img, 0, 0) < 0)
	{
		ft_putendl_fd("Error\nImage to window failed.", 2);
		return (0);
	}
	if (!init_bonus(game))
		return (0);
	return (1);
}

void	render(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	move_player(game);
	update_sprites(game);
	draw_background(game);
	raycast(game);
	draw_sprites(game);
	draw_minimap(game);
}
