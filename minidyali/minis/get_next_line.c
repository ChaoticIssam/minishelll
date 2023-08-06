/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:46:32 by mokhalil          #+#    #+#             */
/*   Updated: 2023/07/25 03:52:35 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*dread(int fd, char *s)
{
	char	*buff;
	int		i;

	if (!s)
		s = ft_calloc(1, 1);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	i = 1;
	while (i != 0)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			free(s);
			return (NULL);
		}
		buff[i] = '\0';
		s = ft_str_join(s, buff);
		if (ft_str_chr(buff, '\n'))
			break ;
	}
	free(buff);
	return (s);
}

char	*read_line(char *save)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	j = 0;
	i = 0;
	while (save[i] && save[i] != '\n')
		line[j++] = save[i++];
	if (save[i] && save[i] == '\n')
		line[j++] = '\n';
	line[j] = 0;
	return (line);
}

char	*update(char *save)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	new = malloc(ft_str_len(save) - i + 1);
	if (!new)
	{
		free(save);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
		new[j++] = save[i++];
	new[j] = 0;
	free(save);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = dread(fd, save);
	if (!save)
		return (NULL);
	line = read_line(save);
	save = update(save);
	return (line);
}
// int main()
// {
// 	char *k;
// 	int i;
// 	i = open("txt.t", O_CREAT| O_RDONLY);
// 	k = get_next_line(i);
// 	printf("%s",k);
// 	while(k)
// 	{
// 		k = get_next_line(i);
// 		printf("%s",k);
// 	}

// }