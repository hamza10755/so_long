/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:05:31 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/02 16:19:25 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_components(t_game *game)
{
	if (game->map)
	{
		game->map->width = 0;
		game->map->height = 0;
		game->map->exit_path = 0;
		game->map->array = NULL;
	}
	if (game->player)
	{
		game->player->x = 0;
		game->player->y = 0;
	}
	if (game->images)
	{
		game->images->wall = NULL;
		game->images->player = NULL;
		game->images->exit = NULL;
		game->images->collectible = NULL;
		game->images->floor = NULL;
		game->images->width = TILE_SIZE;
		game->images->high = TILE_SIZE;
	}
}

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->window = NULL;
	game->total_collectibles = 0;
	game->collectibles_left = 0;
	game->moves = 0;
	game->player_position = 0;
	game->map = malloc(sizeof(t_map));
	game->player = malloc(sizeof(t_player));
	game->images = malloc(sizeof(t_images));
	init_components(game);
}

int	init_window(t_game *game)
{
	int	width;
	int	height;

	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	width = game->map->width * TILE_SIZE;
	height = game->map->height * TILE_SIZE;
	game->window = mlx_new_window(game->mlx, width, height, "so-long");
	if (!game->window)
		return (0);
	if (!load_images(game))
		return (0);
	render_map(game);
	put_image(game, game->images->player, game->player->x, game->player->y);
	return (1);
}

int	load_images(t_game *game)
{
	game->images->wall = mlx_xpm_file_to_image(game->mlx, "assets/wall.xpm",
			&game->images->width, &game->images->high);
	game->images->player = mlx_xpm_file_to_image(game->mlx, "assets/player.xpm",
			&game->images->width, &game->images->high);
	game->images->collectible = mlx_xpm_file_to_image(game->mlx,
			"assets/collectable.xpm", &game->images->width,
			&game->images->high);
	game->images->exit = mlx_xpm_file_to_image(game->mlx, "assets/exit.xpm",
			&game->images->width, &game->images->high);
	game->images->floor = mlx_xpm_file_to_image(game->mlx, "assets/floor.xpm",
			&game->images->width, &game->images->high);
	return (game->images->wall && game->images->player
		&& game->images->collectible && game->images->exit
		&& game->images->floor);
}
