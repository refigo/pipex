/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:34:42 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 13:21:38 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_last_cmd(t_pipex *data, int *pipe_a)
{
	int	fd;
	int	status;

	fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(pipe_a[READ]);
		exit_perror(data, 1);
	}
	status = dup2(pipe_a[READ], STDIN_FILENO);
	close(pipe_a[READ]);
	if (status == -1)
	{
		close(fd);
		exit_perror(data, 1);
	}
	status = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (status == -1)
		exit_perror(data, 1);
}

static void	set_first_cmd(t_pipex *data, int *pipe_a)
{
	int	fd;
	int	status;

	close(pipe_a[READ]);
	fd = open(data->infile, O_RDONLY);
	if (fd == -1)
	{
		close(pipe_a[WRITE]);
		exit_perror(data, 1);
	}
	status = dup2(fd, STDIN_FILENO);
	close(fd);
	if (status == -1)
	{
		close(pipe_a[WRITE]);
		exit_perror(data, 1);
	}
	status = dup2(pipe_a[WRITE], STDOUT_FILENO);
	close(pipe_a[WRITE]);
	if (status == -1)
		exit_perror(data, 1);
}

void	process_child(t_pipex *data, char **envp, int *pipe_a, int i)
{
	if (i == 0)
		set_first_cmd(data, pipe_a);
	else if (i == 1)
		set_last_cmd(data, pipe_a);
	if (execve(data->exec[i], data->command[i], envp) == -1)
	{
		if (access(data->exec[i], X_OK) == -1)
			exit_error_2msg(data, \
				"mgosh: command not found: ", data->command[i][0], 127);
		else
			exit_perror(data, 1);
	}
}

void	process_parent(int pid_child, int *pipe_a, int i)
{
	int	status_buf;

	if (i == 0)
		close(pipe_a[WRITE]);
	else if (i == 1)
		close(pipe_a[READ]);
	waitpid(pid_child, &status_buf, WNOHANG);
}
