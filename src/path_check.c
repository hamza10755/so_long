/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:14:36 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/26 14:03:54 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;
	int		len;

	copy = (char **)malloc(sizeof(char *) * (game->map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->map->height)
	{
		len = ft_strlen(game->map->array[i]);
		copy[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		ft_strlcpy(copy[i], game->map->array[i], len + 1);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **map, int x, int y, t_game *game)
{
	if (y < 0 || x < 0 || map[y] == NULL || map[y][x] == '1'
		|| map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		game->collectibles_left--;
	if (map[y][x] == 'E')
		game->map->exit_path = 1;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, game);
	flood_fill(map, x - 1, y, game);
	flood_fill(map, x, y + 1, game);
	flood_fill(map, x, y - 1, game);
}

int	check_path(t_game *game)
{
	char	**map_copy;
	int		i;
	int		original_collectibles;

	i = 0;
	map_copy = copy_map(game);
	if (!map_copy)
		return (0);
	game->map->exit_path = 0;
	original_collectibles = game->collectibles_left;
	flood_fill(map_copy, game->player->x, game->player->y, game);
	while (i < game->map->height)
		free(map_copy[i++]);
	free(map_copy);
	if (!game->map->exit_path || game->collectibles_left > 0)
	{
		ft_printf("Error\nNo valid path to exit\n");
		return (0);
	}
	game->collectibles_left = original_collectibles;
	return (1);
}
