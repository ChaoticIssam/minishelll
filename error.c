/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:20:53 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/11 01:31:02 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_error(char *list)
{
	int	num;
	int	num1;

	num = num_of_q(list, 0);
	num1 = num_of_s_q(list, 0);
	if (num % 2 != 0 || num1 % 2 != 0)
		lerreurat(3);
	return (1);
}

int	expand_erreur(char *list)
{
	int	i;

	i = 0;
	if (!list)
		return (0);
	while (list[i])
	{
		if (((list[i] == '4' || list[i] == '5') && (list[i + 1] == '4' || list[i
						+ 1] == '5')))
			lerreurat(9);
		i++;
	}
	return (1);
}

int	lerreurat(int error)
{
	if (error == 3)
	{
		printf("ERROR QUOTES!\n");
		exit(0);
	}
	if (error == 6)
	{
		printf("ERROR PIPE!\n");
		exit(0);
	}
	if (error == 9)
	{
		printf("ERROR REDIRECTION!\n");
		exit(0);
	}
	return (0);
}
