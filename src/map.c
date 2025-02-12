/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamzabillah <hamzabillah@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:12:05 by hbelaih           #+#    #+#             */
/*   Updated: 2025/02/12 23:04:18 by hamzabillah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "so_long.h"

static int	close_fd(int fd, int ret)
{
	if (fd >= 0)
		close(fd);
	return (ret);
}

static int	set_map_dimensions(int fd, t_game *game)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (0);
	game->map->width = ft_strlen(line);
	if (line[game->map->width - 1] == '\n')
		game->map->width--;
	game->map->height = 0;
	while (line)
	{
		game->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

int	get_map_dimensions(char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!set_map_dimensions(fd, game))
		return (close_fd(fd, 0));
	return (close_fd(fd, 1));
}

int	read_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0 || !get_map_dimensions(file, game))
		return (0);
	game->map->array = malloc(sizeof(char *) * (game->map->height + 1));
	if (!game->map->array)
		return (close_fd(fd, 0));
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		game->map->array[i++] = line;
	}
	game->map->array[i] = NULL;
	return (close_fd(fd, 1));
}
