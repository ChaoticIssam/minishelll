/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 01:29:48 by mokhalil          #+#    #+#             */
/*   Updated: 2023/07/25 04:21:20 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "minishell.h"
# include "../minishell.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_str_join(char *s1, char *s2);
size_t	ft_str_len(char *str);
char	*get_next_line(int fd);
char	*update(char *save);
char	*ft_str_chr(char *s, char c);
char	*dread(int fd, char *s);
void	*ft_calloc(size_t count, size_t size);
char	*str_cpy(char *dest, char *src);
#endif