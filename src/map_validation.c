/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:13:57 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/01 18:29:37 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_rectangular(t_game *game)
{
	int	i;
	int	len;

	i = 0;
	while (i < game->map->height)
	{
		len = ft_strlen(game->map->array[i]);
		if (len != game->map->width)
			return (0);
		i++;
	}
	return (1);
}

static int	check_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			if ((i == 0 || i == game->map->height - 1 || j == 0
					|| j == game->map->width - 1)
				&& game->map->array[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_cell(t_game *game, int i, int j, int *player, int *exit)
{
	if (game->map->array[i][j] == 'P')
	{
		(*player)++;
		game->player->x = j;
		game->player->y = i;
	}
	else if (game->map->array[i][j] == 'E')
		(*exit)++;
	else if (game->map->array[i][j] == 'C')
		game->total_collectibles++;
	else if (game->map->array[i][j] != '0' && game->map->array[i][j] != '1')
		return (0);
	return (1);
}

static int	check_characters(t_game *game)
{
	int	i;
	int	j;
	int	player;
	int	exit;

	player = 0;
	exit = 0;
	game->total_collectibles = 0;
	i = -1;
	while (++i < game->map->height)
	{
		j = -1;
		while (++j < game->map->width)
		{
			if (!check_cell(game, i, j, &player, &exit))
				return (0);
		}
	}
	game->collectibles_left = game->total_collectibles;
	return (player == 1 && exit == 1 && game->total_collectibles > 0);
}

int	validate_map(t_game *game)
{
	if (!check_rectangular(game))
	{
		ft_printf("Error\nMap is not rectangular\n");
		return (0);
	}
	if (!check_walls(game))
	{
		ft_printf("Error\nMap is not surrounded by walls\n");
		return (0);
	}
	if (!check_characters(game))
	{
		ft_printf("Error\nInvalid map characters\n");
		return (0);
	}
	return (1);
}
