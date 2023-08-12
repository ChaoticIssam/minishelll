/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:28:40 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/12 05:22:28 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_global g;
void	re_vars(t_main *main)
{
	main->i = 0;
	main->j = 0;
	main->x = 0;
}

void	done_normal(t_commandes *tmp, t_env *senv, envar *env, t_bill *bill)
{
	senv->var = fill_var(tmp, env, bill->i, bill->j);
	senv->path = fill_path(env, senv);
	if (senv->var[0] == '?')
	{
		free(tmp->commande[bill->i]);
		tmp->commande[bill->i] = ft_itoa(g.exit_status);
	}
	if (senv->path != NULL)
	{
		free(tmp->commande[bill->i]);
		tmp->commande[bill->i] = senv->path;
	}
	else
		return ;
}

void	check_bill(t_commandes *tmp, t_env *senv, envar *env)
{
	t_bill	*bill;

	bill = my_malloc(sizeof(t_bill));
	bill->i = 0;
	bill->j = 0;
	while (tmp->commande[bill->i])
	{
		if ((tmp->commande[bill->i][bill->j] == '"'
			|| tmp->commande[bill->i][bill->j] == '\'')
				&& tmp->commande[bill->i][bill->j + 1] == '$')
		{
			while (tmp->commande[bill->i][bill->j])
			{
				tmp->commande[bill->i][bill->j] = tmp->commande[bill->i][bill->j
					+ 1];
				bill->j++;
			}
		}
		if (tmp->commande[bill->i][0] == '$')
			done_normal(tmp, senv, env, bill);
		bill->i++;
	}
}

void	siginthandler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
