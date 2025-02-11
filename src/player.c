/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:15:02 by hbelaih           #+#    #+#             */
/*   Updated: 2025/02/11 15:56:46 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (game->map->array[new_y][new_x] == '1')
		return (0);
	return (1);
}

static int	check_win(t_game *game)
{
	ft_printf("Checking win condition... collectibles_left: %d\n",
		game->collectibles_left);
	if (game->collectibles_left == 0
		&& game->map->array[game->player->y][game->player->x] == 'E')
	{
		ft_printf("\nCongratulations! You won in %d moves!\n", game->moves);
		exit_game(game);
		return (1);
	}
	return (0);
}

void	update_player_position(t_game *game, int new_x, int new_y)
{
	if (game->map->array[game->player->y][game->player->x] == 'C')
	{
		game->collectibles_left--;
		ft_printf("Collected collectible. Remaining: %d\n",
			game->collectibles_left);
		game->map->array[game->player->y][game->player->x] = '0';
	}
	put_image(game, game->images->floor, game->player->x, game->player->y);
	game->player->x = new_x;
	game->player->y = new_y;
	game->moves++;
	ft_printf("Moves: %d\n", game->moves);
	render_map(game);
	put_image(game, game->images->player, game->player->x, game->player->y);
	check_win(game);
}

int	move_player(t_game *game, int key)
{
	int	new_x;
	int	new_y;

	new_x = game->player->x;
	new_y = game->player->y;
	if (key == ESC_KEY)
		exit_game(game);
	else if (key == W_KEY)
		new_y--;
	else if (key == S_KEY)
		new_y++;
	else if (key == A_KEY)
		new_x--;
	else if (key == D_KEY)
		new_x++;
	else
		return (0);
	if (is_valid_move(game, new_x, new_y))
		update_player_position(game, new_x, new_y);
	return (0);
}
