/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:11:44 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/07/13 22:23:27 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"

void	t_echo(char **input)
{
	int		isoption;
	int		i;
	int		j;
	int		flprnt;

	flprnt = 0;
	i = 0;
	isoption = 0;
	j = 0;
	while (input[i])
	{
		// Check for the -n option
		j = 1;
		while (input[i][j] == 'n')
		{
			if (input[i][j] != 'n')
			{
				isoption = 0;
				break ;
			}
			j++;
		}
		if (input[i][j] == '\0' && !flprnt)
			isoption = 1;
		if (input[i][j] != '\0' || flprnt)
		{
			flprnt = 1;
			printf("%s", input[i]);
		}
		if ((input[i][j] != '\0' || flprnt) && input[i + 1] != NULL)
			printf(" ");
		i++;
	}
	// Print a new line if -n option is not present
	if (!isoption)
		printf("\n");
}
