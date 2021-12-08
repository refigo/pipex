/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:34:42 by mgo               #+#    #+#             */
/*   Updated: 2021/12/08 19:34:43 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	process_parent(t_pipex *data, int pid_child, int *pipe_a, int i)
{
	int	status;

	if (i == 0)
		close(pipe_a[1]);
	else if (i == 1)
		close(pipe_a[0]);
	waitpid(pid_child, &status, 0);
	return (0);
}

static void	set_last_cmd(t_pipex *data, int *pipe_a)
{
	int	fd;
	int	status;

	fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		close(pipe_a[0]);
		exit_on_error(data, strerror(errno));
	}
	status = dup2(pipe_a[0], STDIN_FILENO);
	close(pipe_a[0]);
	if (status == -1)
	{
		close(fd);
		exit_on_error(data, strerror(errno));
	}
	status = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (status == -1)
		exit_on_error(data, strerror(errno));
}

static void	set_first_cmd(t_pipex *data, int *pipe_a)
{
	int	fd;
	int	status;

	close(pipe_a[0]);
	fd = open(data->infile, O_RDONLY);
	if (fd == -1)
	{
		close(pipe_a[1]);
		exit_on_error(data, strerror(errno));
	}
	status = dup2(fd, STDIN_FILENO);
	close(fd);
	if (status == -1)
	{
		close(pipe_a[1]);
		exit_on_error(data, strerror(errno));
	}
	status = dup2(pipe_a[1], STDOUT_FILENO);
	close(pipe_a[1]);
	if (status == -1)
		exit_on_error(data, strerror(errno));
}

void	process_child(t_pipex *data, char **envp, int *pipe_a, int i)
{
	if (i == 0)
		set_first_cmd(data, pipe_a);
	else if (i == 1)
		set_last_cmd(data, pipe_a);
	execve(data->exec[i], data->command[i], envp);
	exit_properly(data);
}
