/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:12:05 by hbelaih           #+#    #+#             */
/*   Updated: 2025/02/11 17:00:08 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	get_map_dimensions(char *file, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);//check this shit
	if (!line)
	{
		close(fd);
		return (0);
	}
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
	close(fd);
	return (1);
}
int	fd_ftaa7(t_game *game, char *file)
{
	int	fd;

	if (!get_map_dimensions(file, game))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(1);
	return (fd);
}
int	read_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = fd_ftaa7(game, file);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		exit_game(game);
	}
	// game->map->array = malloc(sizeof(char *) * (game->map->height + 1));
	game->map->array = NULL;
	if (!game->map->array)
	{
		close(fd);
		free(line);
		line = get_next_line(fd);
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
		return (0);
	}
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		game->map->array[i++] = line;
		line = get_next_line(fd);
	}
	game->map->array[i] = NULL; // game->mommy = 0;
	close(fd);
	return (1);
}
