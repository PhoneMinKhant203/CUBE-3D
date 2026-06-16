/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 12:26:27 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 14:33:56 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nUsage: ./cub3D ./path-to-map.cub", 2);
		return (1);
	}
	if (!init_game(&game, argv[1]))
	{
		cleanup_game(&game);
		return (1);
	}
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_NORMAL);
	if (!mlx_loop_hook(game.mlx, render, &game))
	{
		ft_putendl_fd("Error\nFailed to set loop hook.", 2);
		cleanup_game(&game);
		return (1);
	}
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
