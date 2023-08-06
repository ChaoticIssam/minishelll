/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 05:23:13 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/07/27 13:14:03 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

envar	*ft_ls_tnew(char *content)
{
	envar	*p;

	p = (envar *)malloc(sizeof(envar));
	if (!p)
		return (NULL);
	p->value = content;
	p->next = NULL;
	return (p);
}

void	ft_ls_tadd_back(envar **lst, envar *ne)
{
	envar	*ptr;

	ptr = *lst;
	if (ne && lst)
	{
		if (*lst == NULL)
		{
			*lst = ne;
		}
		else
		{
			while (ptr->next != NULL)
				ptr = ptr->next;
			ptr->next = ne;
		}
	}
}

int	ft_lstsize(envar *lst)
{
	int		i;
	envar	*ptr;

	ptr = lst;
	i = 0;
	if (!lst)
		return (0);
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
int	ft_lst_size(t_commandes *lst)
{
	int		i;
	t_commandes	*ptr;

	ptr = lst;
	i = 0;
	if (!lst)
		return (0);
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

void	ft_lstdelone(envar *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del(lst->value);
		free(lst);
	}
}
