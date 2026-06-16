/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phonekha <phonekha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 14:40:37 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/11 14:40:50 by phonekha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	skip_spaces(char *line, int i)
{
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

int	parse_num(char *line, int *i, int *num)
{
	int	value;
	int	digits;

	value = 0;
	digits = 0;
	*i = skip_spaces(line, *i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		value = value * 10 + line[*i] - '0';
		if (value > 255)
			return (0);
		digits++;
		(*i)++;
	}
	if (digits == 0)
		return (0);
	*num = value;
	*i = skip_spaces(line, *i);
	return (1);
}

uint32_t	to_rgba(int rgb[3])
{
	return ((rgb[0] << 24) | (rgb[1] << 16) | (rgb[2] << 8) | 0xFF);
}
