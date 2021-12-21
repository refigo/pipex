/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:50:06 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 13:57:56 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include "libft.h"

enum	e_pipe
{
	READ,
	WRITE
};

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	***command;
	char	**path;
	char	**exec;
}				t_pipex;

// set_data.c
void	set_data(t_pipex *data, char **argv, char **envp);

// parsing_quote.c
char	**cmd_splitquote(char *str);

// splitspace_remain.c
int		splitspace_remain(char ***splitted, char *src_tmp);

// process.c
void	process_parent(int pid_child, int *pipe_a, int i);
void	process_child(t_pipex *data, char **envp, int *pipe_a, int i);

// free_data.c
void	free_data(t_pipex *data);

// exit.c
void	exit_perror(t_pipex *data, int code_err);
void	exit_error_2msg(t_pipex *data, char *msg1, char *msg2, int code_err);

// tool_functions.c
int		set_strdup(char **dest, char *src);
int		search_strset(char *str, char *set);
int		find_len2pointer(char **p);
int		free_2pointer(char	**p);
int		free_3pointer(char	***p);

#endif