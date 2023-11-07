/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:00:12 by nesdebie          #+#    #+#             */
/*   Updated: 2023/10/23 12:05:03 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	args_error(int ac, char *filename)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("cub3d: ", 2);
	if (ac == 2)
	{
		ft_putstr_fd(filename, 2);
		ft_putendl_fd(" is not a valid file.", 2);
	}
	if (ac < 2)
		ft_putendl_fd("no argument", 2);
	if (ac > 2)
		ft_putendl_fd("too many arguments", 2);
	ft_putendl_fd("./cub3d <file>.cub", 2);
	return (1);
}

int	xpmfile_error(char *filename, int error)
{
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("cub3d: ", 2);
	ft_putstr_fd(filename, 2);
	if (error == TEXTURE_ACCESS)
		ft_putendl_fd(": file not found", 2);
	if (error == TEXTURE_OPEN)
		ft_putendl_fd(": permission denied", 2);
	if (error == TEXTURE_EXTENSION)
		ft_putendl_fd(" is not a .xpm file", 2);
	return (1);
}

int	mlx_error(int error)
{
	ft_putendl_fd("Error", 2);
	if (error == MLX_INIT)
		ft_putendl_fd("cub3d: mlx: mlx_init() failed", 2);
	else if (error == MLX_WIN)
		ft_putendl_fd("cub3d: mlx: mlx_new_window() failed", 2);
	else if (error == MLX_XPM)
		ft_putendl_fd("cub3d: mlx: mlx_xpm_file_to_image()) failed", 2);
	else if (error == MLX_IMG)
		ft_putendl_fd("cub3d: mlx: mlx_new_image() failed", 2);
	return (1);
}

int	error_msg(int error)
{
	ft_putendl_fd("Error", 2);
	if (error == NO_PLAYER)
		ft_putendl_fd("cub3d: player not found", 2);
	else if (error == TWO_PLAYER)
		ft_putendl_fd("cub3d: too many players found", 2);
	else if (error == NOT_WALLED)
		ft_putendl_fd("cub3d: map not walled", 2);
	else if (error == INVALID_CHAR)
		ft_putendl_fd("cub3d: invalid char", 2);
	else if (error == FILE_ERROR)
		ft_putendl_fd("cub3d: cannot open file", 2);
	else if (error == FORMAT_ERROR)
		ft_putendl_fd("cub3d: invalid file format", 2);
	else if (error == MALLOC_ERROR)
		ft_putendl_fd("cub3d: malloc failed", 2);
	else if (error == RGB_VALUE)
		ft_putendl_fd("cub3d: RGB value not valid", 2);
	else if (error == RGB_FORMAT)
		ft_putendl_fd("cub3d: RGB format not valid", 2);
	return (1);
}
