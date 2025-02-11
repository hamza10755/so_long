/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:15:50 by hbelaih           #+#    #+#             */
/*   Updated: 2025/02/11 15:36:33 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	if (!game || !game->map)
		return ;
	if (game->map->array)
	{
		while (i < game->map->height)
		{
			if (game->map->array[i])
				free(game->map->array[i]);
			i++;
		}
		free(game->map->array);
		game->map->array = NULL;
	}
	free(game->map);
	game->map = NULL;
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
	// game->mlx = NULL;
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
		game->mlx = NULL;
	}
	if (game->map)
		free_map(game);
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
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
