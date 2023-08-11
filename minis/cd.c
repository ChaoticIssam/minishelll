/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:20:35 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/10 06:05:15 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"

void	t_cd(envar **ev, char **input)
{
	envar	*v;
	envar	*s;
	char	*wd;
	char	current_dir[100];
	int		i;

	i = 2;
	v = *ev;
	while (input[i])
	{
		if (input[i])
		{
			printf("Error: too many argument");
			break ;
		}
		i++;
	}
	printf("--->folder %s\n",input[1]);
	if (!input[1] || !strcmp(input[1], "~"))
	{
		while (v)
		{
			if (!ft_str_ncmp(v->value, "HOME", 4))
				break ;
			v = v->next;
		}
		if (!v)
		{
			printf("cd: HOME not set\n");
			return ;
		}
		input[1] = &(v->value[5]);
	}
	if (!strcmp(input[1], "-"))
	{
		s = *ev;
		while (s)
		{
			if (!ft_str_ncmp(s->value, "OLDPWD", 6))
			{
				input[1] = &(s->value[7]);
				if (chdir(input[1]) != 0)
					printf("cd: %s: No such file or directory\n", input[1]);
				else
				{
					if (!getcwd(current_dir, sizeof(current_dir)))
						return ;
					else
					{
						printf("%s\n", current_dir);
						s = *ev;
						while (s)
						{
							if (!ft_str_ncmp(s->value, "PWD", 3))
							{
								wd = ft_strdup(&(s->value[4]));
								free(s->value);
								s->value = ft_strjoin("PWD=", current_dir);
							}
							s = s->next;
						}
						s = *ev;
						while (s)
						{
							if (!ft_str_ncmp(s->value, "OLDPWD", 6))
							{
								free(s->value);
								s->value = ft_strjoin("OLDPWD=", wd);
								break ;
							}
							s = s->next;
						}
						if (s == NULL)
							ft_ls_tadd_back(ev, ft_ls_tnew(ft_strjoin("OLDPWD=", wd)));
					}
				}
				return ;
			}
			s = s->next;
		}
		if (s == NULL)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return ;
		}
	}
	else if (chdir(input[1]) != 0)
		printf("cd: %s: No such file or directory\n", input[1]);
	else
	{
		if (!getcwd(current_dir, sizeof(current_dir)))
		{
			return ;
		}
		s = *ev;
		while (s)
		{
			if (!ft_str_ncmp(s->value, "PWD", 3))
			{
				wd = ft_strdup(&(s->value[4]));
				free(s->value);
				s->value = ft_strjoin("PWD=", current_dir);
			}
			s = s->next;
		}
		s = *ev;
		while (s)
		{
			if (!ft_str_ncmp(s->value, "OLDPWD", 6))
			{
				free(s->value);
				s->value = ft_strjoin("OLDPWD=", wd);
				break ;
			}
			s = s->next;
		}
		if (s == NULL)
			ft_ls_tadd_back(ev, ft_ls_tnew(ft_strjoin("OLDPWD=", wd)));
	}
}
