/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:18:05 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/16 14:56:34 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static char	*copy_path(char *line, int i)
{
	char	*path;
	int		start;
	int		len;

	i = skip_spaces(line, i);
	start = i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	len = i - start;
	if (len <= 0)
		return (NULL);
	i = skip_spaces(line, i);
	if (line[i])
		return (NULL);
	path = ft_substr(line, start, len);
	if (!path)
		return (NULL);
	return (path);
}

static int	load_texture_path(mlx_texture_t **slot, char *path)
{
	*slot = mlx_load_png(path);
	if (!*slot)
	{
		ft_putendl_fd("Error\nFailed to load texture.", 2);
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

static mlx_texture_t	**get_tex_slot(t_game *game, char *line, int *bit)
{
	if (ft_strncmp(line, "NO", 2) == 0 && ft_isspace(line[2]))
	{
		*bit = CFG_NO;
		return (&game->tex.north);
	}
	if (ft_strncmp(line, "SO", 2) == 0 && ft_isspace(line[2]))
	{
		*bit = CFG_SO;
		return (&game->tex.south);
	}
	if (ft_strncmp(line, "WE", 2) == 0 && ft_isspace(line[2]))
	{
		*bit = CFG_WE;
		return (&game->tex.west);
	}
	if (ft_strncmp(line, "EA", 2) == 0 && ft_isspace(line[2]))
	{
		*bit = CFG_EA;
		return (&game->tex.east);
	}
	return (NULL);
}

int	parse_texture(t_game *game, char *line, int *mask)
{
	mlx_texture_t	**slot;
	char			*path;
	int				bit;
	int				i;

	i = skip_spaces(line, 0);
	slot = get_tex_slot(game, line + i, &bit);
	if (!slot)
		return (0);
	if (*mask & bit)
	{
		ft_putendl_fd("Error\nDuplicate texture config.", 2);
		return (-1);
	}
	path = copy_path(line, i + 2);
	if (!path)
	{
		ft_putendl_fd("Error\nInvalid texture path.", 2);
		return (-1);
	}
	if (!load_texture_path(slot, path))
		return (-1);
	*mask |= bit;
	return (1);
}
