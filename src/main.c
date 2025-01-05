/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:11:45 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/05 16:59:42 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_name(char *name)
{
	char	*ber;
	int		i;
	int		j;

	if (ft_strlen(name) < 4)
	{
		write(2, "Error\nmap must name .ber\n", 25);
		exit(1);
	}
	i = 0;
	j = 3;
	ber = ".ber";
	while (name[i])
		i++;
	while (j >= 0)
	{
		if (ber[j--] != name[--i])
		{
			write(2, "Error\nmap must be name .ber\n", 28);
			exit(1);
		}
	}
}

static int	validate_args(int argc, char **argv)
{
	int fd;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long map.ber\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("File does not exist, or can not read it\n");
		return (0);
	}
	check_name(argv[1]);
	return (1);
}

static int	setup_game(t_game *game, char *map_file)
{
	init_game(game);
	if (!read_map(game, map_file))
		{
			cleanup_game(game);
			return (0);
		}
	if (!validate_map(game) || !check_path(game))
	{
		cleanup_game(game);
		return (0);
	}
	if (!init_window(game))
	{
		cleanup_game(game);
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
	
	if (!validate_args(argc, argv))
		return (1);
	game = malloc(sizeof(t_game));
	if (!game)
		return (1);
	if (!setup_game(game, argv[1]))
		{
			free(game);
			return (1);
		}
	mlx_hook(game->window, 17, 0, exit_game, game);
	mlx_key_hook(game->window, key_hook_wrapper, game);
	mlx_loop(game->mlx);
	return (0);
}
