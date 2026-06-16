/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:54:47 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/16 12:42:15 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_cub_file(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '\0');
}

int	is_map_start(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	return (line[i] == '1');
}

int	count_map_lines(char **lines, int start)
{
	int	count;

	count = 0;
	while (lines[start + count])
	{
		if (is_empty_line(lines[start + count]))
			return (-1);
		count++;
	}
	return (count);
}

int	copy_map_line(t_game *game, char **lines, int start, int i)
{
	game->map[i] = ft_strdup(lines[start + i]);
	if (!game->map[i])
	{
		game->map[i] = NULL;
		free_str(game->map);
		game->map = NULL;
		return (0);
	}
	return (1);
}
