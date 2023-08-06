/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokhalil <mokhalil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:00:00 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/06 17:46:30 by mokhalil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"
#include "get_next_line.h"

char	**free_things(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		strings[i] = NULL;
		i++;
	}
	free(strings);
	strings = NULL;
	return (strings);
}

char	**env_tab(envar **ev)
{
	int		i;
	int		size;
	char	**env;
	envar	*tmp;

	size = ft_lstsize(*ev);
	tmp = *ev;
	env = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (tmp)
	{
		env[i] = ft_strdup(tmp->value);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

char	**split_path(envar **ev)
{
	char	**split;
	envar	*env;

	env = *ev;
	while (env && ft_str_ncmp(env->value, "PATH", 4))
		env = env->next;
	if (!env)
		return (NULL);
	split = ft_split(&env->value[5], ':');
	return (split);
}

char	*check_path(char **split, char *cmd)
{
	t_hop	va;

	va.arg = ft_split(cmd, ' ');
	va.i = 0;
	if (access(va.arg[0], X_OK) == 0)
		return (va.arg[0]);
	if (!split)
		return (NULL);
	va.p = ft_strjoin("/", va.arg[0]);
	va.arg = free_things(va.arg);
	while (split[va.i])
	{
		va.k = ft_strjoin(split[va.i], va.p);
		if (access(va.k, X_OK) == 0)
		{
			free(va.p);
			return (va.k);
		}
		free(va.k);
		va.i++;
	}
	free(va.p);
	return (NULL);
}
int	count_heredoc(char *list)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{	
			count++;
			i += 2;
		}
		else
			i++;
	}
	return (count);
}

void	heredoc(t_commandes **c, t_varint *l, char *list)
{
	int		i;
	int		pipe_fd[2];
	int		*pid;
	int		j;

	pid = malloc (sizeof(int) * l->size);
	l->tmp = (*c);
	i = 0;
	l->x = 0;
	j = 0;
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			printf("list--->%s\n", list);
			pipe(pipe_fd);
			pid[j] = fork();
			if (pid[j] < 0)
			{
				printf("Minishel: error fork\n");
				return ;
			}
			if (pid[j] == 0)
			{
				while (1)
				{
					l->line = readline(">");
					if (!l->line)
						break ;
					if (!ft_str_ncmp(l->line,
							l->tmp->files[l->x], ft_strlen(l->line)))
					{
						break ;
					}
				}
				close(pipe_fd[0]);
				write(pipe_fd[1], l->line, ft_strlen(l->line));
				write(pipe_fd[1], "\n", 1);
				close(pipe_fd[1]);
				free(l->line);
			}
			else
			{
				waitpid(pid[j], 0, 0);
				dup2(pipe_fd[0], l->fd_rdc[l->nb_h]);
				close(l->fd_rdc[l->nb_h]);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
				l->x++;
				l->nb_h++;
				j++;
			}
			i += 2;
		}
		else
			i++;
	}
	printf("khrjna\n");
	return ;
}

void	redirection(t_varint *l, char **files, char *list)
{
	char	*line;

	line = NULL;
	l->x = 0;
	l->d = 0;
	l->fd = 0;
	printf("list ->%s\n", list);
	while (list[l->d])
	{
		if (files[l->x])
		{
			if (list[l->d] == '4')
			{
				l->fd = open (files[l->x], O_RDWR);
				dup2(l->fd, 0);
				close(l->fd);
				l->x++;
				printf("l->d %d\n", l->d);
			}
			else if (list[l->d] == '5')
			{
				l->fd = open (files[l->x], O_CREAT | O_TRUNC | O_RDWR);
				dup2(l->fd, 1);
				close(l->fd);
				printf("l->d %d\n", l->d);
				l->x++;
			}
			else if (list[l->d] == '8' && list[l->d + 1] && list[l->d + 1] == '8')
			{
				if (l->fd_rdc[l->nb_h])
				{
					dup2(l->fd_rdc[l->nb_h], 0);
					close (l->fd_rdc[l->nb_h]);
					l->nb_h++;
					l->x++;
					l->d++;
				}
			}
			else if (list[l->d] == '9' && list[l->d + 1] && list[l->d + 1] == '9')
			{
				l->fd = open (files[l->x], O_CREAT | O_WRONLY
						| O_APPEND | O_RDONLY, 0644);
				dup2(l->fd, 1);
				close(l->fd);
				l->x++;
				l->d++;
			}
		}
		l->d++;
	}
	return ;
}

void	multiple_pipe(t_commandes **c, envar **ev, char *list)
{
	t_commandes	*cmd;
	t_varint	*l;
	char		**path_ex;
	char		**list_sp;
	int			pipe_fd[2];
	int			*pid_fd;
	char		*cp;
	int 		s;
	int			i;
	//int 		pid;
	int			old_ifd;
	int			m;

	cmd = *c;
	l = malloc(sizeof(t_varint));
	l->size = count_heredoc(list);
	l->fd_rdc = malloc(sizeof(int) * l->size);
	path_ex = split_path(ev);
	cp = check_path(path_ex, cmd->commande[0]);
	s = ft_lst_size(*c);
	i = 0;
	// if (s == 1)
	// {
	// 	l->nb_h = 0;
	// 	heredoc(&cmd, l, list);
	// 	redirection(l, (*c)->files, list);
	// 	if (exec(ev, cmd->commande))
	// 	{
	// 		// g_global.exit_status = 0;
	// 		return ;
	// 	}
	// 	pid = fork();
	// 	if (pid < 0)
	// 	{
	// 		// g_global.child = 1;
	// 		return ;
	// 	}
	// 	if (pid == 0)
	// 	{
	// 		path_ex = split_path(ev);
	// 		cp = check_path(path_ex, cmd->commande[0]);
	// 		if (!cp)
	// 		{
	// 			free_things(path_ex);
	// 			free(cp);
	// 			write(2, "command not found\n", 18);
	// 			exit(1);
	// 		}
	// 		execve(cp, cmd->commande, env_tab(ev));
	// 		// g_global.exit_status = 127;
	// 		perror("execve");
	// 		// exit(g_global.exit_status);
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	else
	// 	{
	// 		waitpid(pid, 0, 0);
	// 		//return;
	// 	}
	// }
	if (s >= 1)
	{
		list_sp = ft_split(list, '6');
		cmd = *c;
		l->k = 0;
		l->nb_h = 0;
		while (list_sp[l->k])
		{
			heredoc(&cmd, l, list_sp[l->k]);
			l->k++;
		}
		pid_fd = malloc(sizeof(int) * s);
		i = 0;
		old_ifd = 0;
		l->k = 0;
		l->nb_h = 0;
		while (i < s && cmd)
		{
			if (i < s - 1)
			{
				m = pipe(pipe_fd);
				if (m < 0)
				{
					perror("pipe");
					exit(EXIT_FAILURE); 
				}
			}
			l->in = 0;
			l->out = 0;
			pid_fd[i] = fork();
			if (pid_fd[i] < 0)
			{
				printf("Minishel: error fork\n");
				return ;
			}
			if (pid_fd[i] == 0)
			{
				if (s > 1)
				{
					if (i == 0)
					{
						close(pipe_fd[0]);
						dup2(pipe_fd[1], 1);
						close(pipe_fd[1]);
					}
					if (i == s - 1)
					{
						dup2(old_ifd, 0);
						close(old_ifd);
					}
					else if (i > 0 && i < s - 1)
					{
						dup2(old_ifd, 0);
						dup2(pipe_fd[1], 1);
						close(old_ifd);
						close(pipe_fd[0]);
						close(pipe_fd[1]);
					}
				}
				if (list_sp[l->k])
					redirection(l, cmd->files, list_sp[l->k]);
				path_ex = split_path(ev);
				cp = check_path(path_ex, cmd->commande[0]);
				if (!cp)
				{
					write(2, "command not found\n", 18);
					exit(1);
				}
				if (exec(ev, cmd->commande))
				{
					free_things(path_ex);
					free(cp);
					exit(0);
				}
				else
				{
					execve(cp, cmd->commande, env_tab(ev));
					perror("execve");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				waitpid(pid_fd[i], 0, 0);
				close(pipe_fd[1]);
			}
			old_ifd = pipe_fd[0];
			cmd = cmd->next;
			l->k++;
			i++;
		}
		free(pid_fd);
		free_things(list_sp);
	}
	free(l);
	return ;
}
