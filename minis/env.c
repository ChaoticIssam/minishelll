/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:49:47 by mokhalil          #+#    #+#             */
/*   Updated: 2023/07/13 21:35:45 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "minishell.h"

void	env(envar **ev)
{
	int		i;
	envar	*pr;

	pr = *ev;
	i = 0;
	while (pr)
	{
		if (strchr(pr->value, '='))
		{
			write(1, pr->value, ft_strlen(pr->value));
			write(1, "\n", 1);
		}
		pr = pr->next;
	}
}