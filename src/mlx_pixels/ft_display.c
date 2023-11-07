/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:39:09 by hubrygo           #+#    #+#             */
/*   Updated: 2023/11/06 15:31:47 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	create_player(t_game *game, int color)
{
	t_img	player;
	int		i;
	int		j;

	color = (100 << 24) | (255 << 16) | (255 << 8) | 0;
	player.img = NULL;
	init_img(game, &player, 5, 5);
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			set_image_pixel(&player, i, j, color);
			j++;
		}
		i++;
	}
	game->player.img_player = player;
}

void	ft_draw_player(t_game *game)
{
	int	x;
	int	color;
	float	pdx;
	float	pdy;
	int placement_y;
	int placement_x;

	placement_y = (Y / 2) - (game->map_height * 19) / 2;
	placement_x = (X / 2) - (game->map_width * 19) / 2;
	pdx = game->player.pdx;
	pdy = game->player.pdy;
	color = (150 << 24) | (255 << 16) | (255 << 8) | 0;
	create_player(game, color);
	mlx_put_image_to_window(game->mlx, game->win, game->player.img_player.img, (game->player.pos_x * 20) + placement_x, (game->player.pos_y * 20) + placement_y);
	mlx_destroy_image(game->mlx, game->player.img_player.img);
	x = -1;
	while (++x < 7) // longueur
	{
		mlx_pixel_put(game->img, game->win, (game->player.pos_x * 20) + pdx + placement_x, \
						(game->player.pos_y * 20) + placement_y + pdy, color);
		pdy += game->player.dir_y * 2;
		pdx += game->player.dir_x * 2;
	}
}


void	create_wall(t_game *game, int color)
{
	t_img	wall;
	int		y;
	int		x;
	int		i;
	int		j;

	color = (180 << 24) | (0 << 16) | (0 << 8) | 0;
	y = 19;
	x = 19;
	wall.img = NULL;
	init_img(game, &wall, x, y);
	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			set_image_pixel(&wall, i, j, color);
			j++;
		}
		i++;
	}
	game->wall = wall;
}

void	draw_map(t_game *game)
{
	int		i;
	int		j;
	int		color;
	int		placement_x;
	int		placement_y;
	static int	start = 0;

	color = 0;
	placement_y = (Y / 2) - (game->map_height * 19) / 2;
	placement_x = (X / 2) - (game->map_width * 19) / 2;
	if (start == 0)
	{
		create_wall(game, color);
		start++;
	}
	i = 0;
	while (i < game->map_height)
	{
		j = 0;
		while (j < game->map_width)
		{
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall.img, (j * 20) + (placement_x), (i * 20) + placement_y);
			j++;
		}
		i++;
	}
}
