/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <nesdebie@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:02:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/10/25 23:52:39 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_chars(char *str)
{
	int	i;
	int	nb_pl;

	i = 0;
	nb_pl = 0;
	while (str[i])
	{
		if (isinset(str[i], " \n01NSEW"))
			return (error_msg(INVALID_CHAR));
		if (!isinset(str[i], "NSEW"))
			nb_pl++;
		if (nb_pl > 1)
			return (error_msg(TWO_PLAYER));
		i++;
	}
	if (!nb_pl)
		return (error_msg(NO_PLAYER));
	return (0);
}

static int	ft_check_arounds(char **map, int y, int x)
{
	if (!y || !x || !map[y + 1] || !map[y][x + 1])
		return (1);
	if (isinset(map[y - 1][x - 1], "01SNEW"))
		return (1);
	if (isinset(map[y - 1][x], "01SNEW"))
		return (1);
	if (isinset(map[y - 1][x + 1], "01SNEW"))
		return (1);
	if (isinset(map[y][x - 1], "01SNEW"))
		return (1);
	if (isinset(map[y][x + 1], "01SNEW"))
		return (1);
	if (isinset(map[y + 1][x - 1], "01SNEW"))
		return (1);
	if (isinset(map[y + 1][x], "01SNEW"))
		return (1);
	if (isinset(map[y + 1][x + 1], "01SNEW"))
		return (1);
	return (0);
}

static int	check_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!isinset(map[i][j], "0SNEW"))
			{
				if (!i || !j || !map[i + 1] || !map[i][j + 1])
					return (1);
				else if (ft_check_arounds(map, i, j))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_params(t_game *game)
{
	int	i;

	i = 0;
	if (check_chars(game->map_str))
		return (1);
	if (check_textures(game))
		return (1);
	if (game->map_str[ft_strlen(game->map_str) - 1] != '\n')
		game->map_str = ft_strjoingnl(game->map_str, "\n");
	game->map = ft_split(game->map_str, '\n');
	if (!game->map)
		return (error_msg(MALLOC_ERROR));
	if (resize_array(game->map))
		return (error_msg(MALLOC_ERROR));
	if (check_walls(game->map))
		return (error_msg(NOT_WALLED));
	game->map_width = ft_strlen(game->map[0]);
	while (game->map[i])
		i++;
	game->map_height = i;
	return (0);
}
