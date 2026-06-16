/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wintoo <wintoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:46:40 by phonekha          #+#    #+#             */
/*   Updated: 2026/06/16 12:54:43 by wintoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	count_lines(char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static char	**alloc_lines(int count)
{
	char	**lines;

	lines = malloc(sizeof(char *) * (count + 1));
	if (!lines)
		return (NULL);
	lines[0] = NULL;
	return (lines);
}

static int	read_one_line(int fd, char **lines, int i)
{
	int	len;

	lines[i] = get_next_line(fd);
	if (!lines[i])
		return (0);
	len = ft_strlen(lines[i]);
	if (len > 0 && lines[i][len - 1] == '\n')
		lines[i][len - 1] = '\0';
	lines[i + 1] = NULL;
	return (1);
}

static char	**read_lines(char *filename, int count)
{
	char	**lines;
	int		fd;
	int		i;

	lines = alloc_lines(count);
	if (!lines)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(lines);
		return (NULL);
	}
	i = 0;
	while (i < count && read_one_line(fd, lines, i))
		i++;
	close(fd);
	if (i != count)
	{
		free_str(lines);
		return (NULL);
	}
	return (lines);
}

char	**extract_file(char *filename)
{
	int	count;

	if (!is_cub_file(filename))
	{
		ft_putendl_fd("Error\nInvalid file. File format: <filename>.cub", 2);
		return (NULL);
	}
	count = count_lines(filename);
	if (count <= 0)
	{
		ft_putendl_fd("Error\nFailed to read file.", 2);
		return (NULL);
	}
	return (read_lines(filename, count));
}
