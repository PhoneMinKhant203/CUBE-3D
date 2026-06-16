/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phonekha <phonekha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 17:17:48 by wintoo            #+#    #+#             */
/*   Updated: 2026/06/11 14:40:19 by phonekha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	get_color_target(t_game *game, char *line, int *bit, uint32_t **dst)
{
	if (line[0] == 'F' && ft_isspace(line[1]))
	{
		*bit = CFG_F;
		*dst = &game->tex.floor;
		return (1);
	}
	if (line[0] == 'C' && ft_isspace(line[1]))
	{
		*bit = CFG_C;
		*dst = &game->tex.ceiling;
		return (1);
	}
	return (0);
}

static int	parse_rgb(char *line, int i, int rgb[3])
{
	int	idx;

	idx = 0;
	while (idx < 3)
	{
		if (!parse_num(line, &i, &rgb[idx]))
			return (0);
		if (idx < 2 && line[i] != ',')
			return (0);
		if (idx < 2)
			i++;
		idx++;
	}
	i = skip_spaces(line, i);
	if (line[i])
		return (0);
	return (1);
}

int	parse_color(t_game *game, char *line, int *mask)
{
	uint32_t	*dst;
	int			rgb[3];
	int			bit;
	int			i;

	i = skip_spaces(line, 0);
	if (!get_color_target(game, line + i, &bit, &dst))
		return (0);
	if (*mask & bit)
	{
		ft_putstr_fd("Error\nDuplicate color config\n", 2);
		return (-1);
	}
	if (!parse_rgb(line, i + 1, rgb))
	{
		ft_putstr_fd("Error\nInvalid RGB color\n", 2);
		return (-1);
	}
	*dst = to_rgba(rgb);
	*mask |= bit;
	return (1);
}
