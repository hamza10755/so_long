/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:15:50 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/01 18:22:55 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_map(t_game *game)
{
	int	i;

	if (game->map->array)
	{
		i = 0;
		while (game->map->array[i])
		{
			free(game->map->array[i]);
			i++;
		}
		free(game->map->array);
		free(game->map);
	}
}

void	cleanup_images(t_game *game)
{
	if (game->images)
	{
		if (game->images->wall)
			mlx_destroy_image(game->mlx, game->images->wall);
		if (game->images->player)
			mlx_destroy_image(game->mlx, game->images->player);
		if (game->images->collectible)
			mlx_destroy_image(game->mlx, game->images->collectible);
		if (game->images->exit)
			mlx_destroy_image(game->mlx, game->images->exit);
		if (game->images->floor)
			mlx_destroy_image(game->mlx, game->images->floor);
		free(game->images);
	}
}

void	cleanup_game(t_game *game)
{
	if (game->window)
		mlx_destroy_window(game->mlx, game->window);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->map)
	{
		free_map(game);
		free(game->map);
	}
	if (game->player)
		free(game->player);
}

int	exit_game(t_game *game)
{
	cleanup_game(game);
	free(game);
	exit(0);
	return (0);
}