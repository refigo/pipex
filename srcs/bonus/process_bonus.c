/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:34:42 by mgo               #+#    #+#             */
/*   Updated: 2022/04/12 12:54:58 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"



int	get_pipe_index(int *pipes, int index, enum e_pipe ACT)
{
	if (ACT == READ)
		printf("current pipes[%d][READ]: [%d]\n", index, pipes[(index * 2) + ACT]);
	else
		printf("current pipes[%d][WRITE]: [%d]\n", index, pipes[(index * 2) + ACT]);
	return (pipes[(index * 2) + ACT]);
}

void	close_pipe_index(int *pipes, int index, enum e_pipe ACT)
{
	close(pipes[(index * 2) + ACT]);
	// return ?
}


static void	set_first_cmd(t_pipex *data, int *pipes, int i)
{
	int	fd_in;
	int	status;

	// todo: change i to zero(0) and remove i
	close_pipe_index(pipes, 0, READ);

	// set input
	fd_in = open(data->infile, O_RDONLY);
	if (fd_in == -1)
	{
		close_pipe_index(pipes, 0, WRITE);
		exit_perror(data, 1);
	}
	status = dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	if (status == -1)
	{
		close_pipe_index(pipes, 0, WRITE);
		exit_perror(data, 1);
	}

	// set output
	status = dup2(get_pipe_index(pipes, i, WRITE), STDOUT_FILENO);
	close_pipe_index(pipes, i, WRITE);
	if (status == -1)
		exit_perror(data, 1);
}

static void	set_middle_cmd(t_pipex *data, int *pipes, int i)
{
	int	status;

	// set input
	status = dup2(get_pipe_index(pipes, i - 1, READ), STDIN_FILENO);
	close_pipe_index(pipes, i - 1, READ);
	if (status == -1)
		exit_perror(data, 1);

	// set output
	status = dup2(get_pipe_index(pipes, i, WRITE), STDOUT_FILENO);
	close_pipe_index(pipes, i, WRITE);
	if (status == -1)
		exit_perror(data, 1);
}

static void	set_last_cmd(t_pipex *data, int *pipes, int i)
{
	int	fd_out;
	int	status;

	// use data->num_cmd
	// i - 1 == data->num_cmd - 2
	// last_pipe_i = i - 1 or data->num_cmd - 2

	// set input
	printf("set_last_cmd input: [%d]\n", get_pipe_index(pipes, i - 1, READ));
	status = dup2(get_pipe_index(pipes, i - 1, READ), STDIN_FILENO);
	close_pipe_index(pipes, i - 1, READ);
	if (status == -1)
		exit_perror(data, 1);

	// set output
	fd_out = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_perror(data, 1);
	status = dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	if (status == -1)
		exit_perror(data, 1);
}

void	process_child(t_pipex *data, char **envp, int *pipes, int i)
{
	if (i == 0)
		set_first_cmd(data, pipes, i);	// todo: chage for bonus
	else if (i == data->num_cmd - 1)
		set_last_cmd(data, pipes, i);	// todo: chage for bonus
	else
		set_middle_cmd(data, pipes, i); // do!
	
	if (execve(data->exec[i], data->command[i], envp) == -1)
	{
		if (access(data->exec[i], X_OK) == -1)
			exit_error_2msg(data, \
				"mgosh: command not found: ", data->command[i][0], 127);
		else
			exit_perror(data, 1);
	}
}

void	process_parent(t_pipex *data, int pid_child, int *pipes, int i)
{
	int	status_buf;

	// close all pipes?
	// last_cmd_i = data->num_cmd - 1
	if (i == 0)	// todo: change for bonus
		close_pipe_index(pipes, 0, WRITE);
	else if (i == (data->num_cmd - 1))	// todo: change for bonus
		close_pipe_index(pipes, i - 1, READ);
	else
	{
		close_pipe_index(pipes, i - 1, READ);
		close_pipe_index(pipes, i, WRITE);
	}
	waitpid(pid_child, &status_buf, WNOHANG);
	//printf("done index [%d]\n", i);
}
