/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <nesdebie@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:29:08 by nesdebie          #+#    #+#             */
/*   Updated: 2023/10/24 23:34:39 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*ft_space_line(size_t size)
{
	size_t	i;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * size + 1);
	if (!line)
		return (NULL);
	while (i < size)
	{
		line[i] = ' ';
		i++;
	}
	line[i] = 0;
	return (line);
}

static void	ft_resize(char **arr, size_t size)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		tmp = ft_space_line(size - ft_strlen(arr[i]));
		if (!tmp)
		{
			ft_freesplit(arr);
			break ;
		}
		arr[i] = ft_strjoingnl(arr[i], tmp);
		free (tmp);
		i++;
	}
}

int	resize_array(char **map)
{
	int		i;
	size_t	biggest;
	size_t	tmp;

	i = 0;
	biggest = 0;
	while (map[i])
	{
		tmp = ft_strlen(map[i]);
		if (tmp > biggest)
			biggest = tmp;
		i++;
	}
	ft_resize(map, biggest);
	if (!map)
		return (1);
	return (0);
}
