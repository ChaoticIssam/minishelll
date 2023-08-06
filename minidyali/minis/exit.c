/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 01:13:05 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/03 11:38:21 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"

void	t_exit(char **c)
{
	char	**s;
	int		i;

	s = c;
	i = 0;
	if (s[2])
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		return ;
	}
	while (s[1][i])
	{
		if (!ft_isdigit(s[1][i]))
		{
			write(2, "minishell: exit: dsgfd: numeric argument required\n", 51);
			return ;
		}
		i++;
	}
	if (s[1] && ft_atoi(s[1]) >= 0)
		exit(ft_atoi(s[1]));
	else
		exit(1);
}
