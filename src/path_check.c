/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:14:36 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/02 16:35:31 by hbelaih          ###   ########.fr       */
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

static void	flood_fill(char **map, int x, int y, int *collectibles)
{
	if (y < 0 || x < 0 || map[y] == NULL || map[y][x] == '1'
		|| map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		(*collectibles)--;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, collectibles);
	flood_fill(map, x - 1, y, collectibles);
	flood_fill(map, x, y + 1, collectibles);
	flood_fill(map, x, y - 1, collectibles);
}

int	check_exit_reachability(char **map_copy, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if (map_copy[i][j] == 'E')
			{
				if ((i > 0 && map_copy[i - 1][j] == 'F')
					|| (i < game->map->height - 1 && map_copy[i + 1][j] == 'F')
					|| (j > 0 && map_copy[i][j - 1] == 'F')
					|| (j < game->map->width - 1 && map_copy[i][j + 1] == 'F'))
				{
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_path(t_game *game)
{
	char	**map_copy;
	int		collectibles;
	int		exit_found;
	int		i;

	i = 0;
	map_copy = copy_map(game);
	if (!map_copy)
		return (0);
	collectibles = game->total_collectibles;
	flood_fill(map_copy, game->player->x, game->player->y, &collectibles);
	exit_found = check_exit_reachability(map_copy, game);
	while (i < game->map->height)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
	if (exit_found || collectibles > 0)
	{
		ft_printf("Error\nNo valid path to exit\n");
		return (0);
	}
	return (1);
}
