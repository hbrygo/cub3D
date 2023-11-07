/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_checker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <nesdebie@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:02:41 by nesdebie          #+#    #+#             */
/*   Updated: 2023/10/23 09:00:22 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_fc_args(char **arr)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (arr[i])
	{
		if (onlyint(arr[i]))
			error_msg(RGB_FORMAT);
		tmp = ft_atoi(arr[i]);
		if (tmp < 0 || tmp > 255)
			error_msg(RGB_VALUE);
		i++;
	}
	if (i != 3)
		return (error_msg(RGB_FORMAT));
	return (0);
}

static int	check_fc(t_game *game, char c)
{
	char	**arr;

	if (c == 'c')
		arr = ft_split(game->sprites.c, ',');
	if (c == 'f')
		arr = ft_split(game->sprites.f, ',');
	if (!arr)
		return (error_msg(MALLOC_ERROR));
	if (check_fc_args(arr))
	{
		ft_freesplit(arr);
		return (1);
	}
	if (c == 'c')
		game->sprites.c_rgb = set_rgb(ft_atoi(arr[0]),
				ft_atoi(arr[1]), ft_atoi(arr[2]));
	if (c == 'f')
		game->sprites.f_rgb = set_rgb(ft_atoi(arr[0]),
				ft_atoi(arr[1]), ft_atoi(arr[2]));
	ft_freesplit(arr);
	return (0);
}

int	check_xpm(char *texture)
{
	int	fd;

	fd = 0;
	if (check_extension(texture, ".xpm"))
		return (xpmfile_error(texture, TEXTURE_EXTENSION));
	if (access(texture, F_OK) == -1)
		return (xpmfile_error(texture, TEXTURE_ACCESS));
	fd = (open(texture, O_RDONLY, 0777));
	if (fd == -1)
		return (xpmfile_error(texture, TEXTURE_OPEN));
	close (fd);
	return (0);
}

int	check_nsew(t_game *game)
{
	if (check_xpm(game->sprites.no))
		return (1);
	if (check_xpm(game->sprites.so))
		return (1);
	if (check_xpm(game->sprites.ea))
		return (1);
	if (check_xpm(game->sprites.we))
		return (1);
	return (0);
}

int	check_textures(t_game *game)
{
	int	i;

	i = 0;
	while (game->sprites.f[i] && game->sprites.f[i] != '\n')
		i++;
	if (game->sprites.f[i])
		game->sprites.f[i] = 0;
	i = 0;
	while (game->sprites.c[i] && game->sprites.c[i] != '\n')
		i++;
	if (game->sprites.c[i])
		game->sprites.c[i] = 0;
	if (check_fc (game, 'f'))
		return (1);
	if (check_fc (game, 'c'))
		return (1);
	if (check_nsew(game))
		return (1);
	return (0);
}
