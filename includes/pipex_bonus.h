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

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
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

	int		num_cmd;
}				t_pipex;

// set_data_bonus.c
void	set_data(t_pipex *data, int argc, char **argv, char **envp);

// parsing_quote_bonus.c
char	**cmd_splitquote(char *str);

// splitspace_remain_bonus.c
int		splitspace_remain(char ***splitted, char *src_tmp);

// process_bonus.c
//void	process_parent(int pid_child, int *pipe_a, int i);
void	process_parent(t_pipex *data, int pid_child, int *pipes, int i);
void	process_child(t_pipex *data, char **envp, int *pipes, int i);

// free_data_bonus.c
void	free_data(t_pipex *data);

// exit_bonus.c
void	exit_perror(t_pipex *data, int code_err);
void	exit_error_2msg(t_pipex *data, char *msg1, char *msg2, int code_err);

// pipe_function_bonus.c
int		set_pipe_with_index(int *pipes, int index);
int		get_pipe_index(int *pipes, int index, enum e_pipe ACT);
void	close_pipe_index(int *pipes, int index, enum e_pipe ACT);

// tool_function_bonus.c
int		set_strdup(char **dest, char *src);
int		search_strset(char *str, char *set);
int		find_len2pointer(char **p);
int		free_2pointer(char	**p);
int		free_3pointer(char	***p);


int	test_data(t_pipex *data);

#endif