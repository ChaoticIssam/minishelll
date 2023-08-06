/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:20:27 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/04 00:12:15 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"

void	unset(envar **head, char **input)
{
	envar	*current;
	envar	*prev;
	int		i;

	i = 0;
	if (*head == NULL)
	{
		printf("No environment variables to unset.\n");
		return ;
	}
	while (input[i])
	{
		current = *head;
		prev = NULL;
		// Check if the head node needs to be removed
		if (ft_str_ncmp(current->value, input[i], ft_strlen(input[i])) == 0)
		{
			*head = current->next;
			free(current->value);
			free(current);
			printf("Unset %s\n", input[i]);
			return ;
		}
		// Find the environment variable to remove
		while (current != NULL &&
			ft_str_ncmp(input[i], current->value, ft_strlen(input[i])) != 0)
		{
			prev = current;
			current = current->next;
		}
		if (current == NULL)
		{
			printf("%s is not set.\n", input[i]);
			//return ;
		}
		else
		{	
			prev->next = current->next;
			free(current->value);
			free(current);
			printf("Unset %s\n", input[i]);
		}
			i++;
	}
}
