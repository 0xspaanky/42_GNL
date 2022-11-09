/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smounafi <smounafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 23:56:03 by smounafi          #+#    #+#             */
/*   Updated: 2022/11/09 07:53:04 by smounafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_readfile(int fd, char *static_stocker)
{
	int a;
	char *readed_line;
	
	a = 1;
	if(!static_stocker)
		static_stocker = ft_calloc(1,1);
	readed_line = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if(!readed_line)
		return (NULL);
	while(!(ft_strchr(static_stocker,'\n')) && a != 0)
	{
		a = read(fd, readed_line, BUFFER_SIZE);
		if(a == -1)
		{
			free(readed_line);
			free(static_stocker);
			return (NULL);
		}
		readed_line[a] = '\0';
		static_stocker = ft_strjoin(static_stocker, readed_line);
	}
	free(readed_line);
	return (static_stocker);
}

char *ft_line(char *static_stocker)
{
	char *line;
	int i;

	i = 0;
	line = NULL;
	while(static_stocker[i] && static_stocker[i] != '\n')
		i++;
	if(static_stocker[i] == '\0')
		line = malloc((sizeof(char) * i + 1));
	else
		line = malloc((sizeof(char) * i + 2));
	if(!line)
		return (NULL);
	i = 0;
	while(static_stocker[i] && static_stocker[i] != '\n')
	{
		line[i] = static_stocker[i];
		i++; 
	}
	if(static_stocker[i] == '\n')
	{
		line[i] = static_stocker[i];
		i++;
	}
	line[i] = '\0';
	return line;
}

char *ft_nextline(char *static_stocker)
{
	char *line;
	int a;
	int i;

	i = 0;
	while(static_stocker[i] && static_stocker[i] != '\n')
		i++;
	if (!static_stocker[i])
	{
		free(static_stocker);
		return (NULL);
	}
	//printf("%zu\n%d\n", ft_strlen(static_stocker), i);
	line = malloc(sizeof(char) *(ft_strlen(static_stocker) -  i + 1));
	if(!line)
		return (NULL);
	a = 0;
	i++;
	while(static_stocker[i])
	{
		line[a++] = static_stocker[i++];
	}
	//printf("%d\n", a);
	line[a] = '\0';
	free(static_stocker);
	return (line);
}


char *get_next_line(int fd)
{
	static char *static_stocker;
	char *line;

	line = NULL;
	if(fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	static_stocker = ft_readfile(fd, static_stocker);
	if(!static_stocker)
		return (NULL);
	line = ft_line(static_stocker);
	static_stocker = ft_nextline(static_stocker);
	return line;
}

// int main()
// {
//     int fd;
// 	char *res = NULL;
// 	int i = 0;
	
// 	fd = open("test.txt", O_RDONLY);
// 	res = get_next_line(fd);
// 	printf("%s",res);
// 	res = get_next_line(fd);
// 	printf("%s",res);
// }