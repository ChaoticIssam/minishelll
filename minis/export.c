/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 18:28:00 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/07/20 01:58:57 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"

char	*add_quots(char *value)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	while (value[i] && value[i] != '=')
		i++;
	if (value[i] == '=')
	{
		i++;
		buff = malloc(i);
		j = 0;
		while (j < i && value[j])
		{
			buff[j] = value[j];
			j++;
			if (value[j] != '=' && value[j - 1] == '=')
				break ;
		}
		buff[j] = '\0';
		return (ft_strjoin(ft_strjoin(ft_strjoin(buff, "\""), &value[i]), "\""));
	}
	else
		return (value);
}

int	check_ifinput_true(char *input)
{
	int		i;

	i = 1;
	if (!ft_isalpha(input[0]) && input[0] != '_')
		return (-1);
	while (input[i]&&
		(ft_isalpha(input[i]) || ft_isdigit(input[i]) || input[i] == '_' || input[i] == '+'))
	{
		if (input[i] == '+')
		{
			if (input[i + 1] && input[i + 1] == '=')
				return (1);
			return (-1);
		}
		if (input[i] == '=')
			return (1);
		i++;
	}
	if (input[i] != '=' && input[i] != '\0')
		return (-1);
	return (1);
}

void	t_export(envar **env, char **input)
{
	envar	*ne;
	envar	*pr;
	char	*s;
	char	*nv;
	int		i;
	int		j;
	int		l;
	int		a;
	int		exist;

	pr = *env;
	ne = NULL;
	exist = 0;
	if (*input == NULL)
	{
		while (pr)
		{
			s = ft_strjoin("declare -x ", add_quots(pr->value));
			write(1, s, ft_strlen(s));
			write(1, "\n", 1);
			pr = pr->next;
			free(s);
		}
		return ;
	}
	else
	{
		l = 0;
		while (input[l])
		{
			a = 1;
			if (check_ifinput_true(input[l]) == -1)
			{
				printf("minishell: export: %s: not a valid identifier\n", input[l]);
				a = 0;
			}
			printf("input---->%s\n", input[l]);
			pr = *env;
			while (pr)
			{
				if (!ft_str_ncmp(input[l], pr->value, ft_strlen(input[l])))
				{
					printf("breaak elm3lm\n");
					a = 0;
					break ;
				}
				pr = pr->next;
			}
			if (a)
			{
				i = 0;
				while (input[l][i])
				{
					if (input[l][i] == '+' &&
						input[l][i + 1] && input[l][i + 1] == '=')
					{
						j = 0;
						while (input[l][j] && input[l][j] != '+')
							j++;
						pr = *env;
						while (pr)
						{
							if (!ft_str_ncmp(pr->value, input[l], j))
							{
								printf("%d that are compared = %d\n",j,ft_str_ncmp(pr->value, input[l], j));
								nv = ft_strcat(&(input[l][j + 2]), pr->value);
								printf("nv string concatenat %s\n", nv);
								free(pr->value);
								pr->value = nv;
								exist = 1;
								a = 1;
								break ;
							}
							pr = pr->next;
						}
						if (pr == NULL)
						{
							a = 1;
							ne = ft_ls_tnew(ft_str_rmc(input[l]));
							if (ne != NULL)
							{	
								ft_ls_tadd_back(env, ne);
								exist = 1;
							}
							break ;
						}
					}
					else if (input[l][i] == '=' && input[l][i - 1] != '+')
					{
						printf("mrhba bik m3a =\n");
						j = 0;
						while (input[l][j] && input[l][j] != '=')
							j++;
						pr = *env;
						while (pr)
						{
							if (!ft_str_ncmp(pr->value, input[l], j))
							{
								free(pr->value);
								pr->value = ft_strdup(input[l]);
								exist = 1;
								break ;
							}
							pr = pr->next;
						}
					}
					i++;
				}
			}
			if (a == 1 && !exist)
			{
				ne = ft_ls_tnew(ft_strdup(input[l]));
				if (ne != NULL)
				{
					printf("add node\n");
					ft_ls_tadd_back(env, ne);
				}
			}
			if (a == 0)
			{
				l++;
				continue ;
			}
			l++;
		}
	}
}
