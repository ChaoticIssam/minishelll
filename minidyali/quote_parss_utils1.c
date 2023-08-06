/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parss_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:17:43 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/04 16:52:43 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	frst_s_q(char *tknz)
{
	int	i;

	i = 0;
	while (tknz[i])
	{
		if (tknz[i] == '0')
			return (i);
		i++;
	}
	return (0);
}

int	frst_q_rex(char *tknz, int start)
{
	if (tknz[start - 1] == '1')
	{
		while (start >= 0)
		{
			if (tknz[start - 1] == '2' || start == 0)
				return (start);
			start--;
		}
	}
	return (start);
}

int	num_of_q(char *list, int start)
{
	int	count;

	count = 0;
	while (list[start])
	{
		if (list[start] == '3')
			count++;
		start++;
	}
	return (count);
}

int	num_of_s_q(char *list, int start)
{
	int	count;

	count = 0;
	while (list[start])
	{
		if (list[start] == '0')
			count++;
		start++;
	}
	return (count);
}
