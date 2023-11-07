/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <nesdebie@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:01:49 by nesdebie          #+#    #+#             */
/*   Updated: 2023/10/22 18:42:02 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_texture(t_game *game, char *line, int ret)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (!arr)
		return (error_msg(MALLOC_ERROR));
	if (arr[1] == 0 || arr[2] != 0)
	{
		ft_freesplit(arr);
		return (error_msg(FORMAT_ERROR));
	}
	if (!ft_strncmp(arr[0], "NO", 3))
		ret = add_no(game, arr);
	else if (!ft_strncmp(arr[0], "SO", 3))
		ret = add_so(game, arr);
	else if (!ft_strncmp(arr[0], "WE", 3))
		ret = add_we(game, arr);
	else if (!ft_strncmp(arr[0], "EA", 3))
		ret = add_ea(game, arr);
	else if (!ft_strncmp(arr[0], "F", 2))
		ret = add_fc(game, arr, 'f');
	else if (!ft_strncmp(arr[0], "C", 2))
		ret = add_fc(game, arr, 'c');
	ft_freesplit(arr);
	return (ret);
}

static int	read_map(t_game *game, char *tmp, int fd)
{
	game->map_str = ft_calloc(1, 1);
	if (!game->map_str)
	{
		free(tmp);
		return (error_msg(MALLOC_ERROR));
	}
	while (tmp)
	{
		if (tmp[0] == '\n')
		{
			free(tmp);
			return (error_msg(FORMAT_ERROR));
		}
		game->map_str = ft_strjoingnl(game->map_str, tmp);
		free(tmp);
		if (!game->map_str)
			return (error_msg(MALLOC_ERROR));
		tmp = get_next_line(fd);
	}
	free (tmp);
	if (!game->map_str)
		return (error_msg(FORMAT_ERROR));
	close (fd);
	return (0);
}

int	read_file(t_game *game, char *filename, int fd, char *tmp)
{
	fd = open(filename, O_RDONLY);
	if (fd < 1)
		return (error_msg(FILE_ERROR));
	tmp = get_next_line(fd);
	while (tmp && game->flags.cnt != 6)
	{
		if (tmp[0] != '\n')
		{
			if (parse_texture(game, tmp, 1))
			{
				free(tmp);
				return (error_msg(FORMAT_ERROR));
			}
			game->flags.cnt++;
		}
		free (tmp);
		tmp = get_next_line(fd);
	}
	while (tmp && tmp[0] == '\n')
	{
		free (tmp);
		tmp = get_next_line(fd);
	}
	return (read_map(game, tmp, fd));
}

int	check_extension(char *filename, char *str)
{
	unsigned long	i;

	i = 0;
	if (!ft_strnstr(filename, str, ft_strlen(filename)))
		return (1);
	else
	{
		while (i < ft_strlen(filename) - 4)
			i++;
		if (ft_strncmp(&filename[i], str, 5))
			return (1);
	}
	return (0);
}
