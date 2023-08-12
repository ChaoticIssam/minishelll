/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:00:00 by mokhalil          #+#    #+#             */
/*   Updated: 2023/08/12 02:21:56 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../minishell.h"
char	buffer[100000];
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
	if (!list)
		return (0);
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
int	count_last_inf_heredoc(char *list)
{
	int	i;
	int	flag;
	int	counter;

	counter = 0;
	flag = 0;
	i = 0;
	if (!list)
		return (0);
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			flag = 1;
			i += 2;
		}
		else if (list[i] == '4')
		{
			flag = 0;
			i++;
		}
		else if (list[i] == '6' && flag)
		{
			counter++;
			i++;
			flag = 0;
		}
		else
			i++;
	}
	if (flag)
		counter++;
	return (counter);
}

char	*get_first_infile(char **files, char *list)
{
	int		i;
	int		j;
	char	*in_file;

	in_file = NULL;
	j = -1;
	i = 0;
	while (list[i])
	{
		if (list[i] == '9' && list[i + 1] && list[i + 1] == '9')
		{
			j++;
			i += 2;
		}
		else if (list[i] == '5')
		{
			j++;
			i++;
		}
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			j++;
			if (in_file)
				free(in_file);
			in_file = ft_strdup(files[j]);
			i += 2;
		}
		else if (list[i] == '4')
		{
			j++;
			if (in_file)
				free(in_file);
			in_file = ft_strdup(files[j]);
			i++;
		}
		else
			i++;
	}
	return (in_file);
}

char	*get_first_outfile(char **files, char *list)
{
	int		i;
	int		j;
	char	*out_file;

	out_file = NULL;
	j = -1;
	i = 0;
	while (list[i])
	{
		if (list[i] == '8' && list[i + 1] && list[i + 1] == '8')
		{
			j++;
			i += 2;
		}
		else if (list[i] == '4')
		{
			j++;
			i++;
		}
		if (list[i] == '9' && list[i + 1] && list[i + 1] == '9')
		{
			j++;
			if (out_file)
				free(out_file);
			out_file = ft_strdup(files[j]);
			i += 2;
		}
		else if (list[i] == '5')
		{
			j++;
			if (out_file)
				free(out_file);
			out_file = ft_strdup(files[j]);
			i++;
		}
		else
			i++;
	}
	return (out_file);
}

void	heredoc(t_commandes **c, t_varint *l, char *list)
{
	int		i;
	int		*pid;
	int		j;
	char	*k;
	int		o;
	char	*tmp;
	char	*in_file;
	int		m;

	m = -1;
	k = NULL;
	pid = malloc (sizeof(int) * l->size);
	l->tmp = (*c);
	i = 0;
	l->x = 0;
	j = 0;
	o = 0;
	in_file = get_first_infile(l->tmp->files, list);
	printf("infile here %s\n",in_file);
	printf("file here %s\n",l->tmp->files[0]);
	while (list[o])
	{
		if (list[o] == '8' && list[o + 1] && list[o + 1] == '8')
		{
			if (!strcmp(in_file, l->tmp->files[l->x]))
			{
				m = pipe(l->pipe_fd);
				if (m < 0)
				{
					perror("pipe");
					exit(EXIT_FAILURE);
				}
				l->fd_rdc[l->nb_h] = l->pipe_fd[0];
				printf("fd here %d\n",l->fd_rdc[l->nb_h]);
				printf("return pipe %d\n",m);
			}
			pid[j] = fork();
			if (pid[j] < 0)
			{
				printf("Minishel: error fork\n");
				return ;
			}
			if (pid[j] == 0)
			{
				//close(l->pipe_fd[0]);
				printf("----->%d\n", o);
				i = 0;
				while (1)
				{
					l->line = readline(">");
					if (!strcmp(l->line,
							l->tmp->files[l->x]))
					{
						if (!strcmp(in_file, l->tmp->files[l->x]))
						{
							if (!m)
							{
								printf("kydkhl hna\n");
								write(l->pipe_fd[1], k, ft_strlen(k));
								close(l->pipe_fd[1]);
							}
						}
						if (k)
							free(k);
						exit(0);
					}
					if (i == 0)
						k = ft_strjoin(l->line, "\n");
					else
					{
						tmp = k;
						k = ft_strjoin(tmp, l->line);
						free(tmp);
						tmp = k;
						k = ft_strjoin(tmp, "\n");
						free(tmp);
					}
					i++;
				}
				exit(0);
			}
			else
			{
				waitpid(pid[j], 0, 0);
				//close(l->pipe_fd[1]);
				if (!strcmp(in_file, l->tmp->files[l->x]))
					l->nb_h++;
			}
			j++;
			l->x++;
			o += 2;
		}
		else
			o++;
	}
}

void	redirection(t_varint *l, char **files, char *list)
{
	int		i;
	int		fd;
	char	*in_file;
	char	*out_file;

	fd = -1;
	i = 0;
	l->x = 0;
	l->d = 0;
	in_file = get_first_infile(files,list);
	out_file = get_first_outfile(files,list);
	while (list[l->d])
	{
		if (files[l->x])
		{
			if (list[l->d] == '4')
			{
				printf("infile\n");
				fd = open (files[l->x], O_RDWR);
				if (!strcmp(files[l->x],in_file))
					l->in = fd;
				else
					close(fd);
				l->x++;
			}
			else if (list[l->d] == '5')
			{
				printf("outfile\n");
				fd = open (files[l->x], O_CREAT | O_TRUNC | O_RDWR, 0644);
				if (!strcmp(files[l->x],out_file))
					l->out = fd;
				else
					close(fd);
				l->x++;
			}
			else if (list[l->d] == '8' && list[l->d + 1] && list[l->d + 1] == '8')
			{
				printf("heredoc\n");
				if (!strcmp(files[l->x], in_file))
				{
					l->in = l->fd_rdc[l->nb_h];
					l->nb_h++;
				}
				l->x++;
				l->d++;
			}
			else if (list[l->d] == '9' && list[l->d + 1] && list[l->d + 1] == '9')
			{
				printf("append\n");
				fd = open (files[l->x], O_CREAT | O_WRONLY
						| O_APPEND | O_RDONLY, 0644);
				if (!strcmp(files[l->x],out_file))
					l->out = fd;
				else
					close(fd);
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
	int			pipe_fd[2] = {-1, -1};
	int			*pid_fd;
	char		*cp;
	int 		s;
	int			i;
	int			old_ifd;
	int			m;
	
	if (list[0])
	{
		int t = count_last_inf_heredoc(list);
		printf("counter %d\n",t);
		cmd = *c;
		l = malloc(sizeof(t_varint));
		l->size = count_heredoc(list);
		printf("l->size %d\n",l->size);
		l->pipe_fd[0] = -1;
		l->pipe_fd[1] = -1;
		s = ft_lst_size(*c);
		printf("----****%d\n", s);
		i = 0;
		l->fd_rdc = malloc(sizeof(int) * t);
		l->nb_h = 0;
		if (s == 1)
		{
			int	stin = dup(0);
			int stout = dup(1);
			if(cmd->files)
			{
				printf("hna\n");
				heredoc(&cmd, l, list);
				close(l->pipe_fd[1]);
				l->in = -1;
				l->out = -1;
				l->nb_h = 0;
				// int y = read (l->fd_rdc[l->nb_h],buffer,1000);
				// printf("fd heredoc -> %d\n",l->fd_rdc[l->nb_h]);
				// printf("return read -> %d\n",y);
				// printf("buffer heredoc -> %s\n",buffer);
				redirection(l, cmd->files, list);
			}
			if (l->in != -1)
			{
				dup2(l->in, 0);
				close(l->in);
			}
			if (l->out != -1)
			{
				dup2(l->out, 1);
				close(l->out);
			}
			if(cmd->commande[0])
			{
				if (exec(ev, cmd->commande))
				{
					if (l->in != -1)
						close(l->in);
					if (l->out != -1)
						close(l->out);
					dup2(stout, 1);
					dup2(stin, 0);
					return ;
				}
				else
				{
					l->pid = fork();
					if (l->pid < 0)
					{
						printf("Minishel: error fork\n");
						return ;
					}
					else if (l->pid == 0)
					{
						close(l->pipe_fd[1]);
						path_ex = split_path(ev);
						cp = check_path(path_ex, cmd->commande[0]);
						if (!cp)
						{
							write(2, "command not found\n", 18);
							exit(1);
						}
						execve(cp, cmd->commande, env_tab(ev));
						perror("execve");
						exit(EXIT_FAILURE);
					}			
					else
					{
						waitpid(l->pid, 0, 0);
						dup2(stout, 1);
						dup2(stin, 0);
					}
				}
			}
			return ;
		}
		else if (s > 1)
		{
			pid_fd = malloc(sizeof(int) * s);
			list_sp = ft_split(list, '6');
			cmd = *c;
			l->k = 0;
			l->nb_h = 0;
			if(cmd->files)
			{
				while (list_sp[l->k])
				{
					heredoc(&cmd, l, list_sp[l->k]);
					close(l->pipe_fd[1]);
					l->k++;
					cmd = cmd->next;
				}
			}
				printf("fd heredoc -> %d\n",l->fd_rdc[0]);
			// i = 0;
			// while(i < t)
			// {
			// 	printf("fd heredoc -> %d\n",l->fd_rdc[l->nb_h]);
			// 	i++;
			// 	l->nb_h++;
			// }
			cmd = *c;
			i = 0;
			old_ifd = 0;
			l->k = 0;
			l->nb_h = 0;
			while (i < s)
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
				l->in = -1;
				l->out = -1;
				pid_fd[i] = fork();
				if (pid_fd[i] < 0)
				{
					printf("Minishel: error fork\n");
					return ;
				}
				else if (pid_fd[i] == 0)
				{
					printf("-->list %s\n",list_sp[l->k]);
					if (cmd->files && list_sp[l->k])
						redirection(l, cmd->files, list_sp[l->k]);
					if (i == 0)
					{
						close(pipe_fd[0]);
						if (l->in != -1)
						{
							dup2(l->in, 0);
							close(l->in);
						}
						if (l->out != -1)
						{
							dup2(l->out, 1);
							close(l->out);
						}
						else
							dup2(pipe_fd[1], 1);
					}
					if (i == s - 1)
					{
						if (l->out != -1)
						{
							dup2(l->out, 1);
							close(l->out);
						}
						if (l->in != -1)
						{
							dup2(l->in, 0);
							close(l->in);
						}
						else
						{
							dup2(old_ifd, 0);
							close(old_ifd);
						}
					}
					else if (i > 0)
					{
						if (l->out != -1)
						{
							dup2(l->out, 1);
							close(l->out);
						}
						else
						{
							dup2(pipe_fd[1], 1);
							close(pipe_fd[1]);
						}
						if (l->in != -1)
						{
							dup2(l->in, 0);
							close(l->in);
						}
						else
						{
							dup2(old_ifd, 0);
							close(old_ifd);
						}
					}
					if(cmd->commande[0])
					{
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
					exit(0);
				}
				if (i > 0)
					close(old_ifd);
				old_ifd = pipe_fd[0];
				close(pipe_fd[1]);
				cmd = cmd->next;
				l->k++;
				i++;
			}
			i = 0;
			while (i < s)
				waitpid(pid_fd[i++], 0, 0);
			if (s > 1)
			{
				close(old_ifd);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			free(pid_fd);
			free_things(list_sp);
		}
		// if (!cmd->commande[0] && cmd->files[0])
		// {
		// 	list_sp = ft_split(list, '6');
		// 	cmd = *c;
		// 	l->k = 0;
		// 	l->nb_h = 0;
		// 	while (list_sp[l->k] && cmd)
		// 	{
		// 		heredoc(&cmd, l, list_sp[l->k]);
		// 		close(l->pipe_fd[1]);
		// 		l->k++;
		// 		cmd = cmd->next;
		// 	}
		// 	return ;
		// }
		free(l);
	}
	return ;
}
