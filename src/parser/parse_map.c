/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:54:18 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/16 14:24:14 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	parse_config_line(t_game *game, char *line, int *mask)
{
	int	status;

	status = parse_texture(game, line, mask);
	if (status != 0)
		return (status);
	status = parse_color(game, line, mask);
	if (status != 0)
		return (status);
	ft_putendl_fd("Error\nInvalid config line.", 2);
	return (-1);
}

static int	find_map_start(t_game *game, char **lines, int *mask)
{
	int	i;
	int	status;

	i = 0;
	while (lines[i] && !is_map_start(lines[i]))
	{
		if (!is_empty_line(lines[i]))
		{
			status = parse_config_line(game, lines[i], mask);
			if (status < 0)
				return (-1);
		}
		i++;
	}
	if (!lines[i])
	{
		ft_putendl_fd("Error\nMissing map.", 2);
		return (-1);
	}
	return (i);
}

int	parse_map(t_game *game, char **lines, int start)
{
	int	count;
	int	i;

	count = count_map_lines(lines, start);
	if (count <= 0)
	{
		ft_putendl_fd("Error\nInvalid map section.", 2);
		return (0);
	}
	game->map = malloc(sizeof(char *) * (count + 1));
	if (!game->map)
		return (0);
	i = 0;
	while (i < count)
	{
		if (!copy_map_line(game, lines, start, i))
			return (0);
		i++;
	}
	game->map[i] = NULL;
	return (1);
}

static int	process_map_data(t_game *game, char **lines)
{
	int	start;
	int	mask;

	mask = 0;
	start = find_map_start(game, lines, &mask);
	if (start < 0)
		return (0);
	if (mask != CFG_ALL)
	{
		ft_putendl_fd("Error\nMissing config value.", 2);
		return (0);
	}
	if (!parse_map(game, lines, start))
		return (0);
	return (validate_map(game));
}

int	parse_cub(t_game *game, char *filename)
{
	char	**lines;
	int		status;

	lines = extract_file(filename);
	if (!lines)
		return (0);
	status = process_map_data(game, lines);
	free_str(lines);
	return (status);
}
