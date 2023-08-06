/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:06:30 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/07/17 02:45:22 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"

envar	*get_env(envar *head, char **env)
{
	int		i;
	envar	*pt;

	head = NULL;
	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (ft_str_ncmp("OLDPWD=", env[i], 7) != 0)
			{
				pt = ft_ls_tnew(ft_strdup(env[i]));
				ft_ls_tadd_back(&head, pt);
			}
			i++;
		}
		return (head);
	}
	else
		return (NULL);
}