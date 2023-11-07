/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <nesdebie@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:05:19 by nesdebie          #+#    #+#             */
/*   Updated: 2023/10/22 18:41:58 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	add_ea(t_game *game, char **arr)
{
	int	i;

	i = 0;
	if (game->flags.e_flag > 0)
		return (error_msg(FORMAT_ERROR));
	game->sprites.ea = ft_strdup(arr[1]);
	if (!game->sprites.ea)
		return (error_msg(MALLOC_ERROR));
	game->flags.e_flag++;
	while (game->sprites.ea[i] && game->sprites.ea[i] != '\n')
		i++;
	if (game->sprites.ea[i])
		game->sprites.ea[i] = 0;
	return (0);
}

int	add_we(t_game *game, char **arr)
{
	int	i;

	i = 0;
	if (game->flags.w_flag > 0)
		return (error_msg(FORMAT_ERROR));
	game->sprites.we = ft_strdup(arr[1]);
	if (!game->sprites.we)
		return (error_msg(MALLOC_ERROR));
	game->flags.w_flag++;
	while (game->sprites.we[i] && game->sprites.we[i] != '\n')
		i++;
	if (game->sprites.we[i])
		game->sprites.we[i] = 0;
	return (0);
}

int	add_so(t_game *game, char **arr)
{
	int	i;

	i = 0;
	if (game->flags.s_flag > 0)
		return (error_msg(FORMAT_ERROR));
	game->sprites.so = ft_strdup(arr[1]);
	if (!game->sprites.so)
		return (error_msg(MALLOC_ERROR));
	game->flags.s_flag++;
	while (game->sprites.so[i] && game->sprites.so[i] != '\n')
		i++;
	if (game->sprites.so[i])
		game->sprites.so[i] = 0;
	return (0);
}

int	add_no(t_game *game, char **arr)
{
	int	i;

	i = 0;
	if (game->flags.n_flag > 0)
		return (error_msg(FORMAT_ERROR));
	game->sprites.no = ft_strdup(arr[1]);
	if (!game->sprites.no)
		return (error_msg(MALLOC_ERROR));
	game->flags.n_flag++;
	while (game->sprites.no[i] && game->sprites.no[i] != '\n')
		i++;
	if (game->sprites.no[i])
		game->sprites.no[i] = 0;
	return (0);
}

int	add_fc(t_game *game, char **arr, char flag)
{
	if (flag == 'f')
	{
		if (game->flags.f_flag > 0)
			return (error_msg(FORMAT_ERROR));
		game->sprites.f = ft_strdup(arr[1]);
		if (!game->sprites.f)
			return (error_msg(MALLOC_ERROR));
		game->flags.f_flag++;
	}
	if (flag == 'c')
	{
		if (game->flags.c_flag > 0)
			return (error_msg(FORMAT_ERROR));
		game->sprites.c = ft_strdup(arr[1]);
		if (!game->sprites.c)
			return (error_msg(MALLOC_ERROR));
		game->flags.c_flag++;
	}
	return (0);
}
