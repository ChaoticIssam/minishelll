/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iszitoun <iszitoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 17:05:34 by buyt_mkh7         #+#    #+#             */
/*   Updated: 2023/08/13 05:46:57 by iszitoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../minishell.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// extern t_global		g_global;
//ls >out | wc
typedef struct s_commandes
{
	char **commande; //ls
	char **files;    //out //1105***
	struct s_commandes	*next;
}						t_commandes;

typedef struct s_sig
{
	int					exit_s;
	int					execc;
	int					readline;
	int					process;
}						t_sig;

extern t_sig			g_sigs;

typedef struct s_list
{
	char				*commande;
	struct s_list		*next;
}						t_list;

typedef struct EnvVar
{
	char				*value;
	struct EnvVar		*next;
}						envar;

typedef struct s_hip
{
	int					i;
	char				*p;
	char				*k;
	char				**arg;
}						t_hop;

typedef struct s_varint
{
	int					in;
	int					out;
	int					fd;
	int					k;
	int					d;
	int					x;
	int					size;
	t_commandes			*tmp;
	char				*line;
	int					*fd_rdc;
	int					nb_h;
	int					pipe_fd[2];
	int					pid;
}						t_varint;

envar					*ft_ls_tnew(char *content);
void					ft_ls_tadd_back(envar **lst, envar *ne);
int						exec(envar **env, char **input);
void					t_export(envar **env, char **input);
void					t_cd(envar **ev, char **input);
void					t_echo(char **input);
void					t_pwd(void);
void					t_exit(char **c);
int						ft_str_ncmp(char *s1, char *s2, int n);
char					*ft_strdup(char *s1);
int						ft_strlen(char *str);
char					*ft_strjoin(char *s1, char *s2);
// envar	*get_env(envar *head,char **env);
void					env(envar **ev);
void					unset(envar **head, char **value);
char					*ft_strcat(char *src, char *dst);
char					*ft_str_rmc(char *src);
char					*ft_strchr(char *s, int c);
int						ft_isalpha(int c);
char					**ft_split(char *str, char c);
int						ft_isdigit(int c);
int						ft_lstsize(envar *lst);
int						ft_lst_size(t_commandes *lst);
int						ft_atoi(const char *str);
#endif
