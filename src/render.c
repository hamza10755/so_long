/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:15:18 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/06 14:12:23 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->window, img, x * TILE_SIZE, y
		* TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->height)
	{
		x = 0;
		while (x < game->map->width)
		{
			if (game->map->array[y][x] == '0')
				put_image(game, game->images->floor, x, y);
			else if (game->map->array[y][x] == '1')
				put_image(game, game->images->wall, x, y);
			else if (game->map->array[y][x] == 'C')
				put_image(game, game->images->collectible, x, y);
			else if (game->map->array[y][x] == 'E')
				put_image(game, game->images->exit, x, y);
			x++;
		}
		y++;
	}
	put_image(game, game->images->player, game->player->x, game->player->y);
}
