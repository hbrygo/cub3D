/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:22 by nesdebie          #+#    #+#             */
/*   Updated: 2023/11/07 18:39:50 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	init_binary_screen(t_game *game)
{
	int	i;

	if (game->binary_screen)
		free_tab((void **)game->binary_screen);
	game->binary_screen = ft_calloc(Y + 1, sizeof * game->binary_screen);
	if (!game->binary_screen)
	{
		clear_args(game);
		exit (EXIT_FAILURE); // PAS AU POINT IMO (leaks)
	}
	i = 0;
	while (i < Y)
	{
		game->binary_screen[i] = ft_calloc(X + 1, sizeof * game->binary_screen);
		if (!game->binary_screen[i])
		{
			clear_args(game);
			exit (EXIT_FAILURE); // PAS AU POINT IMO (leaks)
		}
		i++;
	}
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->pixel_bits = 0;
	img->size_line = 0;
	img->endian = 0;
}

void	init_img(t_game *game, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(game->mlx, width, height);
	if (image->img == NULL)
	{
			clear_args(game);
			exit (EXIT_FAILURE); // PAS AU POINT IMO (leaks)
	}
	image->addr = (int *)mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
}

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * (image->size_line / 4) + x;
	image->addr[pixel] = color;
}

static void	set_frame_image_pixel(t_game *game, t_img *image, int x, int y)
{
	unsigned long tmp = set_rgb(128, 128, 128); // print des murs gris en attendant
	if (game->binary_screen[y][x] > 0)
		set_image_pixel(image, x, y, tmp);
	else if (y < Y / 2)
		set_image_pixel(image, x, y, game->sprites.c_rgb);
	else if (y < Y - 1)
		set_image_pixel(image, x, y, game->sprites.f_rgb);
}

static void	render_frame(t_game *game)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(game, &image, X, Y);
	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			set_frame_image_pixel(game, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
	mlx_destroy_image(game->mlx, image.img);
}

void	display_screen(t_game *game)
{
	init_binary_screen(game); // split de calloc de taille X x Y
	init_pov(&game->ray); // set les donnees raycast
	raycasting(&game->player, game);
	render_frame(game); // put image to window
	
	//if (map) {DO MAP STUFF}
}

void	set_dir(t_game *game)
{
	t_player	*p;
	double		rotspeed;
	double		tmp_x;

	rotspeed = ROTSPEED;
    if (game->mouse_x < X / 2)
	    rotspeed *= -1;
	p = &game->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
}

int	cub3d(t_game *game)
{
	if (game->key_pressed == 1)
	{
		mlx_mouse_hide();
		mlx_mouse_get_pos(game->win, &game->mouse_x, &game->mouse_y);
		mlx_mouse_move(game->win, X / 2, Y / 2);
		if (game->mouse_x != X / 2)
			set_dir(game);
	}
	ft_move_player(game);
	if (game->key_pressed == 0)
		mlx_mouse_show();
	display_screen(game);
	if (game->player.map == 1)
	{
		draw_map(game);
		ft_draw_player(game);
	}
	return (0);
}

static	int init_params(t_game *game)
{
	if (init_window(game))
		return (clear_args(game));
	if (init_textures(game))
		return (clear_args(game));
	init_player(game, 0, -1);
	init_dir(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2 || argc > 2)
		return (args_error(argc, NULL));
	init_flags(&game);
	if (parsing(&game, argv[1], argc))
		return (1);
	if (init_params(&game))
		return (1);
	//print_params(&game); // DEBUG
	display_screen(&game);
	mlx_hook(game.win, PRESS_KEY, 0, &key_press, &game);
	mlx_hook(game.win, RELEASE_KEY, 0, &key_release, &game);
	mlx_hook(game.win, RED_CROSS, 0, &close_game, &game);
	mlx_loop_hook(game.mlx, &cub3d, &game);
	mlx_loop(game.mlx);
	return (0);
}
