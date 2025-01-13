/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:05:31 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/13 17:15:53 by hbelaih          ###   ########.fr       */
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

int	init_game(t_game *game)
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
	if (!game->map || !game->player || !game->images)
	{
		ft_printf("ERROR: Failed to allocate memory for game components\n");
		exit_game(game);
		return (0);
	}
	init_components(game);
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_printf("ERROR: Failed to initialize MLX\n");
		exit_game(game);
		return (0);
	}
	load_images(game);
	return (1);
}

int	init_window(t_game *game)
{
	int	width;
	int	height;

	width = game->map->width * TILE_SIZE;
	height = game->map->height * TILE_SIZE;
	game->window = mlx_new_window(game->mlx, width, height, "so-long");
	if (!game->window)
	{
		ft_printf("ERROR: Failed to create game window\n");
		exit_game(game);
		return (0);
	}
	render_map(game);
	put_image(game, game->images->player, game->player->x, game->player->y);
	return (1);
}

void	load_images(t_game *game)
{
	if (!game->mlx || !game->images)
	{
		ft_printf("ERROR: MLX or images not initialized\n");
		exit_game(game);
	}
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
	if (!game->images->wall || !game->images->player
		|| !game->images->collectible || !game->images->exit
		|| !game->images->floor)
	{
		ft_printf("ERROR: Failed to load one or more images\n");
		exit_game(game);
	}
}
