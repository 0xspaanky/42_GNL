/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smounafi <smounafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:55:07 by smounafi          #+#    #+#             */
/*   Updated: 2022/11/10 00:12:49 by smounafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_readfile(int fd, char *static_stocker)
{
	char	*readed_line;
	int		n_readed;

	if (!static_stocker)
		static_stocker = ft_calloc(1, 1);
	n_readed = 1;
	readed_line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!readed_line)
		return (NULL);
	while (!ft_strchr(static_stocker, '\n') && n_readed != 0)
	{
		n_readed = read(fd, readed_line, BUFFER_SIZE);
		if (n_readed == -1)
		{
			free(readed_line);
			free(static_stocker);
			return (NULL);
		}
		readed_line[n_readed] = '\0';
		static_stocker = ft_strjoin(static_stocker, readed_line);
		if (!static_stocker)
			return (NULL);
	}
	free(readed_line);
	return (static_stocker);
}

char	*ft_line(char *static_stocker)
{
	char	*line;
	int		i;

	i = 0;
	if (!static_stocker[i])
		return (NULL);
	while (static_stocker[i] && static_stocker[i] != '\n')
		i++;
	line = malloc((sizeof(char) * i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (static_stocker[i] && static_stocker[i] != '\n')
	{
		line[i] = static_stocker[i];
		i++;
	}
	if (static_stocker[i] == '\n')
	{
		line[i] = static_stocker[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_nextline(char *static_stocker)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (static_stocker[i] && static_stocker[i] != '\n')
		i++;
	if (!static_stocker[i])
	{
		free(static_stocker);
		return (NULL);
	}
	line = malloc(sizeof(char) * (ft_strlen(static_stocker) - i + 1));
	if (!line)
		return (NULL);
	j = 0;
	i++;
	while (static_stocker[i])
	{
		line[j++] = static_stocker[i++];
	}
	line[j] = '\0';
	free(static_stocker);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*static_stocker[OPEN_MAX];
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_stocker[fd] = ft_readfile(fd, static_stocker[fd]);
	if (!static_stocker[fd])
		return (NULL);
	line = ft_line(static_stocker[fd]);
	static_stocker[fd] = ft_nextline(static_stocker[fd]);
	return (line);
}
