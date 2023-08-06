/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:58:37 by iszitoun          #+#    #+#             */
/*   Updated: 2023/08/06 17:50:24 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_read_line(t_main *main)
{
	printf("\033[0;31m");
	main->line = readline("Minishell$ ");
	printf("\033[0m");
	add_history(main->line);
	main->m = my_malloc(sizeof(t_commandes));
	main->tmp = main->m;
	if (main->line == NULL || !ft_strncmp(main->line, "exit"))
		exit(0);
	main->list = toknz_list(main->line, 0, 0);
	printf("list ->%s\n", main->list);
}

void	print_before_pipe(t_main *main)
{
	while (main->tmp->commande[main->j])
	{
		ft_putstr(main->tmp->commande[main->j]);
		printf("<-commandes before pipe\n");
		main->j++;
	}
	while (main->tmp->files[main->x])
	{
		ft_putstr(main->tmp->files[main->x]);
		printf("<-files before pipe\n");
		main->x++;
	}
}

void	print_after_pipe(t_main *main)
{
	while (main->tmp->commande[main->j])
	{
		ft_putstr(main->tmp->commande[main->j]);
		printf("<-commande after pipe\n");
		main->j++;
	}
	while (main->tmp->files[main->x])
	{
		ft_putstr(main->tmp->files[main->x]);
		printf("<-files after pipe\n");
		main->x++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_main	*main;
	envar	*ev;

	(void)ac;
	(void)av;
	ev = 0;
	ev = get_env(ev, env);
	main = my_malloc(sizeof(t_main));
	int_main(main);
	while (1)
	{
		tcgetattr(0, &main->term);
		int_sig_main(main);
		signal(SIGINT, siginthandler);
		ft_read_line(main);
		int_main_before(main);
		check_bill(main->tmp, main->senv, ev);
		print_before_pipe(main);
		int_main_after(main);
		check_bill(main->tmp, main->senv, ev);
		print_after_pipe(main);
		free(main->line);
		multiple_pipe(&main->m, &ev, main->list);
		re_vars(main);
	}
}
