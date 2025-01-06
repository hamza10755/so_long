/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:15:50 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/06 14:12:24 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map(t_game *game)
{
	int	i;

	if (!game || !game->map)
		return ;
	if (game->map->array)
	{
		i = 0;
		while (i < game->map->height && game->map->array[i])
		{
			free(game->map->array[i]);
			i++;
		}
		free(game->map->array);
		game->map->array = NULL;
	}
	free(game->map);
}

static void	destroy_image(void *mlx, void **img)
{
	if (*img)
	{
		mlx_destroy_image(mlx, *img);
		*img = NULL;
	}
}

void	cleanup_images(t_game *game)
{
	if (!game || !game->mlx || !game->images)
		return ;
	destroy_image(game->mlx, (void **)&game->images->wall);
	destroy_image(game->mlx, (void **)&game->images->player);
	destroy_image(game->mlx, (void **)&game->images->collectible);
	destroy_image(game->mlx, (void **)&game->images->exit);
	destroy_image(game->mlx, (void **)&game->images->floor);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->images)
	{
		cleanup_images(game);
		free(game->images);
		game->images = NULL;
	}
	if (game->window && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free_map(game);
	free(game->player);
}

int	exit_game(t_game *game)
{
	if (game)
	{
		cleanup_game(game);
		free(game);
	}
	exit(0);
	return (0);
}
