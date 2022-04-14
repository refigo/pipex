/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:41:03 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:41:06 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include "libft.h"

enum	e_bool
{
	FALSE,
	TRUE
};

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
	int		is_heredoc;
	char	*limiter;
	int		fd_heredoc;

	int		*pipes;
	pid_t	*pids;
}				t_pipex;

// set_data_bonus.c
void	set_data(t_pipex *data, int argc, char **argv, char **envp);

// heredoc_bonus.c
void	confirm_heredoc_shifting_sequence(t_pipex *data, \
											int *argc, char ***argv);
void	set_heredoc_as_infile_and_input(t_pipex *data, char **argv);

// parsing_quote_bonus.c
char	**cmd_splitquote(char *str);

// splitspace_remain_bonus.c
int		splitspace_remain(char ***splitted, char *src_tmp);

// run_pipex_bonus.c
int		run_pipex(t_pipex *data, char **envp);

// process_bonus.c
void	process_parent(t_pipex *data, int i);
void	process_child(t_pipex *data, char **envp, int i);

// free_data_bonus.c
void	free_data(t_pipex *data);

// func_exit_bonus.c
void	exit_perror(t_pipex *data, int code_err);
void	exit_error_2msg(t_pipex *data, char *msg1, char *msg2, int code_err);

// func_pipe_pid_bonus.c
void	calloc_pipes_and_pids(t_pipex *data);
int		set_pipe_index(int *pipes, int index);
int		get_pipe_index(int *pipes, int index, enum e_pipe ACT);
void	close_pipe_index(int *pipes, int index, enum e_pipe ACT);

// func_tool_bonus.c
int		set_strdup(char **dest, char *src);
int		search_strset(char *str, char *set);
int		find_len2pointer(char **p);
int		free_2pointer(char	**p);
int		free_3pointer(char	***p);

#endif
