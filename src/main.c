/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:11:45 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/01 18:25:32 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	validate_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long map.ber\n");
		return (0);
	}
	if (!ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])))
	{
		ft_printf("Error\nInvalid map extension\n");
		return (0);
	}
	return (1);
}

static int	setup_game(t_game *game, char *map_file)
{
	init_game(game);
	if (!read_map(game, map_file))
		return (0);
	if (!validate_map(game) || !check_path(game))
	{
		cleanup_game(game);
		cleanup_images(game);
		return (0);
	}
	if (!init_window(game))
	{
		cleanup_game(game);
		cleanup_images(game);
		return (0);
	}
	return (1);
}

int	key_hook_wrapper(int key, void *param)
{
	move_player((t_game *)param, key);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!validate_args(argc, argv))
		return (1);
	if (!setup_game(game, argv[1]))
		return (1);
	mlx_hook(game->window, 17, 0, exit_game, game);
	mlx_key_hook(game->window, key_hook_wrapper, game);
	mlx_loop(game->mlx);
	return (0);
}
