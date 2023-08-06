/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 02:26:04 by mokhalil          #+#    #+#             */
/*   Updated: 2023/07/25 03:51:40 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_join(char *s1, char *s2)
{
	char	*p;
	char	*start;

	if (!s1 || !s2)
		return (0);
	p = (char *)malloc(ft_str_len(s1) + ft_str_len(s2) + 1);
	if (!p)
		return (0);
	start = p;
	p = str_cpy(p, s1);
	p += ft_str_len((s1));
	p = str_cpy(p, s2);
	p += ft_str_len((s2));
	*p = '\0';
	free(s1);
	return (start);
}

size_t	ft_str_len(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_str_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	if (c == '\0')
		return (s + i);
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	i;

	if (count && size >= SIZE_MAX / count)
		return (0);
	res = malloc(count * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		*((unsigned char *)(res + i)) = 0;
		i++;
	}
	return (res);
}

char	*str_cpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
