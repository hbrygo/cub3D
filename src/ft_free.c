/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:03:27 by nesdebie          #+#    #+#             */
/*   Updated: 2023/10/19 15:46:57 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_freesplit(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
		free(arr[i++]);
	free(arr[i]);
	free(arr);
}

int	clear_args(t_game *game)
{
	if (game->flags.n_flag > 0)
		free(game->sprites.no);
	if (game->flags.s_flag > 0)
		free(game->sprites.so);
	if (game->flags.e_flag > 0)
		free(game->sprites.ea);
	if (game->flags.w_flag > 0)
		free(game->sprites.we);
	if (game->flags.f_flag > 0)
		free(game->sprites.f);
	if (game->flags.c_flag > 0)
		free(game->sprites.c);
	if (game->map_str)
		free(game->map_str);
	if (game->map)
		ft_freesplit(game->map);
	if (game->sprites.n)
		mlx_destroy_image(game->mlx, game->sprites.n);
	if (game->sprites.s)
		mlx_destroy_image(game->mlx, game->sprites.s);
	if (game->sprites.e)
		mlx_destroy_image(game->mlx, game->sprites.e);
	if (game->sprites.w)
		mlx_destroy_image(game->mlx, game->sprites.w);
	return (1);
}
