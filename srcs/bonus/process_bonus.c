/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:42:05 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:42:08 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	set_first_cmd(t_pipex *data)
{
	int	fd_in;
	int	status;

	close_pipe_index(data->pipes, 0, READ);
	fd_in = open(data->infile, O_RDONLY);
	if (fd_in == -1)
	{
		close_pipe_index(data->pipes, 0, WRITE);
		exit_perror(data, 1);
	}
	status = dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	if (status == -1)
	{
		close_pipe_index(data->pipes, 0, WRITE);
		exit_perror(data, 1);
	}
	status = dup2(get_pipe_index(data->pipes, 0, WRITE), STDOUT_FILENO);
	close_pipe_index(data->pipes, 0, WRITE);
	if (status == -1)
		exit_perror(data, 1);
}

static void	set_middle_cmd(t_pipex *data, int i)
{
	int	status;

	status = dup2(get_pipe_index(data->pipes, i - 1, READ), STDIN_FILENO);
	close_pipe_index(data->pipes, i - 1, READ);
	if (status == -1)
		exit_perror(data, 1);
	status = dup2(get_pipe_index(data->pipes, i, WRITE), STDOUT_FILENO);
	close_pipe_index(data->pipes, i, WRITE);
	if (status == -1)
		exit_perror(data, 1);
}

static void	set_last_cmd(t_pipex *data)
{
	int	fd_out;
	int	status;
	int	last_pipe_i;

	last_pipe_i = data->num_cmd - 2;
	status = dup2(get_pipe_index(data->pipes, last_pipe_i, READ), STDIN_FILENO);
	close_pipe_index(data->pipes, last_pipe_i, READ);
	if (status == -1)
		exit_perror(data, 1);
	if (data->is_heredoc)
		fd_out = open(data->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd_out = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_perror(data, 1);
	status = dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	if (status == -1)
		exit_perror(data, 1);
}

void	process_child(t_pipex *data, char **envp, int i)
{
	int	last_cmd_i;

	last_cmd_i = data->num_cmd - 1;
	if (i == 0)
		set_first_cmd(data);
	else if (i == last_cmd_i)
		set_last_cmd(data);
	else
		set_middle_cmd(data, i);
	if (execve(data->exec[i], data->command[i], envp) == -1)
	{
		if (access(data->exec[i], X_OK) == -1)
			exit_error_2msg(data, \
				"mgosh: command not found: ", data->command[i][0], 127);
		else
			exit_perror(data, 1);
	}
}

void	process_parent(t_pipex *data, int i)
{
	int	last_cmd_i;

	last_cmd_i = data->num_cmd - 1;
	if (i == 0)
		close_pipe_index(data->pipes, 0, WRITE);
	else if (i == last_cmd_i)
		close_pipe_index(data->pipes, i - 1, READ);
	else
	{
		close_pipe_index(data->pipes, i - 1, READ);
		close_pipe_index(data->pipes, i, WRITE);
	}
}
