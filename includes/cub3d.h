/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hubrygo < hubrygo@student.s19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:11:57 by nesdebie          #+#    #+#             */
/*   Updated: 2023/11/07 18:32:45 by hubrygo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> // DEBUG
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
//# include <mlx.h>
# include "../libft/libft.h"

# define X	1000
# define Y	1000

# define SPEED 7
# define ROTSPEED 0.07

# define KEY_ESC	53
# define KEY_Q      12

# define KEY_W	13
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2
# define KEY_SPACE	49

# define KEY_M 46

# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_UP	126
# define KEY_DOWN	125

# define RED_CROSS 17
# define PRESS_KEY 2
# define RELEASE_KEY 3

# define PI 3.1415926535

typedef enum s_error
{
	FILE_ERROR,
	FORMAT_ERROR,
	MALLOC_ERROR,
	NO_PLAYER,
	TWO_PLAYER,
	NOT_WALLED,
	INVALID_CHAR,
	TEXTURE_ACCESS,
	TEXTURE_EXTENSION,
	TEXTURE_OPEN,
	RGB_VALUE,
	RGB_FORMAT,
	MLX_WIN,
	MLX_INIT,
	MLX_XPM,
	MLX_IMG
}	t_error;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_player
{
	float	dir;
	float	pdx;
	float	pdy;
	int		up;
	int 	down;
	int 	left;
	int 	right;
	int		turn_left;
	int		turn_right;
	int		augment_move_speed;
	int		downgrade_move_speed;
	int		current_speed;
	
	//RAYCASTING
	char	first_dir;
	float	pos_x; // pos_x map
	float	pos_y; // pos_y map
	float	dir_x; // dir map
	float	dir_y; // dir map
	float	plane_x;
	float	plane_y;

	//MINIMAP
	int		map;
	float	px; //SUPPR
	float	py; //SUPPR
	t_img	img_player;
}				t_player;

typedef struct s_spr
{
	void	*n;
	void	*s;
	void	*w;
	void	*e;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	unsigned long		f_rgb;
	unsigned long		c_rgb;
}				t_spr;

typedef struct s_flag
{
	int	l_flag;
	int	p_flag;
	int	n_flag;
	int	s_flag;
	int	w_flag;
	int	e_flag;
	int	c_flag;
	int	f_flag;
	int	cnt;
}				t_flag;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		**map;
	int			map_width;
	int			map_height;
	int			**binary_screen;
	char		*map_str;
	int			held_key;
	int			key_pressed;
	int			mouse_x;
	int			mouse_y;
	t_img		wall;
	t_ray		ray;
	t_spr		sprites;
	t_flag		flags;
	t_player	player;
}				t_game;

/* ERRORS */
int		args_error(int ac, char *filename);
int		error_msg(int error);
int		xpmfile_error(char *filename, int error);
int		mlx_error(int error);

/* READER */
int		read_file(t_game *game, char *filename, int fd, char *tmp);

/* PARSING */
int		parsing(t_game *game, char *map, int argc);
int		check_params(t_game *game);
int		check_extension(char *filename, char *ext);
int		check_textures(t_game *game);
int		check_nsew(t_game *game);

/* INIT */
void	init_player(t_game *game, int x, int y);
int		init_textures(t_game *game);
int		init_window(t_game *game);
void	init_flags(t_game *game);
void	init_pov(t_ray *ray);

/* FREE */
void	ft_freesplit(char **arr);
int		clear_args(t_game *game);

/* TEMP */
int		add_ea(t_game *game, char **arr);
int		add_we(t_game *game, char **arr);
int		add_so(t_game *game, char **arr);
int		add_no(t_game *game, char **arr);
int		add_fc(t_game *game, char **arr, char flag);

/* SETTER */
unsigned long	set_rgb(int r, int g, int b);

/* UTILS */
int		isinset(char c, char *set);
int		resize_array(char **map);
int		onlyint(char *s);

/*Key event*/
void	wait_inputs(t_game *game);
int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);
int		close_game(t_game *game);

/*DISPLAY (Hugo)*/
void	draw_map(t_game *game);
void	ft_draw_player(t_game *game);

/* DISPLAYS (Nestor) */
void	init_img(t_game *game, t_img *image, int width, int height);
void	set_image_pixel(t_img *image, int x, int y, int color);
void	ft_update_dir(t_game *game);
void	init_dir(t_game *game);
void	ft_move_player(t_game *game);
int		rotate(t_game *game);
void	raycasting(t_player *player, t_game *game);

#endif