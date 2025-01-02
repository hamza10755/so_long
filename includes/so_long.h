/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <hbelaih@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:05:02 by hbelaih           #+#    #+#             */
/*   Updated: 2025/01/02 16:41:01 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE_SIZE 64
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100

typedef struct s_map
{
	int			width;
	int			height;
	int			exit_path;
	char		**array;
}				t_map;

typedef struct s_player
{
	int			x;
	int			y;
}				t_player;

typedef struct s_images
{
	void		*wall;
	int			high;
	int			width;
	void		*player;
	void		*exit;
	void		*collectible;
	void		*floor;
}				t_images;

typedef struct s_game
{
	t_map		*map;
	t_player	*player;
	t_images	*images;
	int			total_collectibles;
	int			collectibles_left;
	int			player_position;
	int			player_count;
	int			exit_count;
	int			moves;
	void		*mlx;
	void		*window;
}				t_game;

void			init_game(t_game *game);
int				init_window(t_game *game);
int				load_images(t_game *game);
void			put_image(t_game *game, void *img, int x, int y);

int				read_map(t_game *game, char *file);
int				validate_map(t_game *game);
int				check_path(t_game *game);

int				move_player(t_game *game, int key);
void			update_player_position(t_game *game, int new_x, int new_y);

void			render_map(t_game *game);

void			free_map(t_game *game);
void			cleanup_game(t_game *game);
int				exit_game(t_game *game);
void			cleanup_images(t_game *game);

#endif
