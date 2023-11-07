/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:05:08 by nesdebie          #+#    #+#             */
/*   Updated: 2023/11/06 13:46:08 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	set_binary_screen(t_game *game, t_ray *ray, int x)
{
	int			y;
	int			i;
	int			color;

	y = ray->draw_start;
	i = 0;
	while (y < Y - 1 && i < ray->line_height)
	{
		color = 1;
		game->binary_screen[y][x] = color;
		y++;
		i++;
	}
}

static void	init_raycasting(int x, t_ray *ray, t_player *player)
{
	init_pov(ray);
	ray->camera_x = 2 * x / (double)X - 1;
	ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
	//printf("cam:%f\ndx:%f\ndy:%f\nmapx:%i\nmapy:%i\ndeltax:%f\ndeltay:%f\n", ray->camera_x, ray->dir_x, ray->dir_y, ray->map_x, ray->map_y, ray->deltadist_x, ray->deltadist_y);
}

static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0) // WEST
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->map_x) * ray->deltadist_x;
	}
	else // EAST
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->dir_y < 0) // NORTH
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->map_y) * ray->deltadist_y;
	}
	else // SOUTH
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

static void	dda(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25 || ray->map_x < 0.25)
			break ;
		else if (ray->map_y > game->map_height - 0.25)
			break ;
		else if (ray->map_x > game->map_width - 1.25)
			break ;
		else if (game->map[ray->map_y][ray->map_x] > '0')
			hit = 1;
	}
}

static void	calculate_line_height(t_ray *ray, t_player *player)
{
	(void) player;
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(Y / ray->wall_dist);
	ray->draw_start = Y / 2 - ((ray->line_height) / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
}

void	raycasting(t_player *player, t_game *game)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = game->ray;
	while (x < X)
	{
		init_raycasting(x, &ray, player);
		set_dda(&ray, player);
		dda(game, &ray);
		calculate_line_height(&ray, player);
		set_binary_screen(game, &ray, x);
		x++;
	}
}

