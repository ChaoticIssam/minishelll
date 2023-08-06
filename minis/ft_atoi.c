/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 11:25:01 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/03 11:30:45 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"
#include <limits.h>

int	ft_atoi(const char *str)
{
	int	n;
	int	s;
	int	i;

	n = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		n = (n * 10) + str[i] - '0';
		if (n > INT_MAX && s == 1)
			return (-1);
		if (n - 1 > INT_MAX && s == -1)
			return (-2);
		i++;
	}
	return (n * s);
}
