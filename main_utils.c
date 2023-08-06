/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:26:12 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/05 21:23:55 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_main(t_main *main)
{
	main->i = 0;
	main->j = 0;
	main->x = 0;
	main->senv = my_malloc(sizeof(t_env));
	main->tmp = NULL;
	main->term2 = main->term;
}

void	int_main_before(t_main *main)
{
	main->m->commande = return_commande(main->list, main->line, 1, 0);
	main->m->files = return_file(main->list, main->line, 1, main->tmp);
	main->m->next = NULL;
}

void	int_main_after(t_main *main)
{
	main->j = 0;
	main->x = 0;
	ft_lstadd_back(&main->tmp, ft_lstnew(main->line));
	main->tmp = main->tmp->next;
	main->tmp->commande = return_commande(main->list, main->line, 0, 0);
	main->tmp->files = return_file(main->list, main->line, 0, main->tmp);
}

void	int_sig_main(t_main *main)
{
	main->term2 = main->term;
	main->term.c_lflag &= ~ISIG;
	main->term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &main->term);
}
