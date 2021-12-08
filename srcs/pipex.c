/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:49:46 by mgo               #+#    #+#             */
/*   Updated: 2021/12/04 11:49:50 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** =============================================================================
** free.c
** =============================================================================
*/

static void	free_command(t_pipex *data)
{
	int	i;
	int	j;

	if (data->command)
	{
		i = -1;
		while (data->command[++i])
		{
			j = -1;
			while (data->command[i][++j])
				free(data->command[i][j]);
			free(data->command[i]);
		}
		free(data->command);
		data->command = 0;
	}
}

static void	free_path(t_pipex *data)
{
	int	i;

	if (data->path)
	{
		i = -1;
		while (data->path[++i])
		{
			free(data->path[i]);
		}
		free(data->path);
		data->path = 0;
	}
}

static void	free_exec(t_pipex *data)
{
	int	i;

	if (data->exec)
	{
		i = -1;
		while (data->exec[++i])
		{
			free(data->exec[i]);
		}
		free(data->exec);
		data->exec = 0;
	}
}

void	free_data(t_pipex *data)
{
	free_command(data);
	free_path(data);
	free_exec(data);
}

/*
** =============================================================================
** exit.c
** =============================================================================
*/

void	exit_on_error(t_pipex *data)
{
	free_data(data);
	// errno, perror, strerror
}

void	exit_properly(t_pipex *data)
{
	free_data(data);
	exit(0);
}

/*
** =============================================================================
** pipex.c
** =============================================================================
*/

int	process_parent(t_pipex *data, int pid_child, int *pipe_a, int i)
{
	int	status;

	if (i == 0)
		close(pipe_a[1]);
	else
		close(pipe_a[0]);
	waitpid(pid_child, &status, 0);
	return (0);
}

int	process_child(t_pipex *data, char **envp, int *pipe_a, int i)
{
	int	fd;

	if (i == 0)
	{
		close(pipe_a[0]);
		fd = open(data->infile, O_RDONLY);
		// todo: exception
		dup2(fd, STDIN_FILENO);
		// todo: exception
		close(fd);
		dup2(pipe_a[1], STDOUT_FILENO);
		// todo: exception
		close(pipe_a[1]);
	}
	else
	{
		fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// todo: exception
		dup2(pipe_a[0], STDIN_FILENO);
		// todo: exception
		close(pipe_a[0]);
		dup2(fd, STDOUT_FILENO);
		// todo: exception
		close(fd);
	}
	execve(data->exec[i], data->command[i], envp);
	exit(0);
	// todo: free data
	return (0);
}

int	pipex(t_pipex *data, char **envp)
{
	int	pipe_a[2];
	pid_t	pid_child;
	int	i;

	pipe(pipe_a);
	// todo: exception
	i = -1;
	while (++i < 2)
	{
		pid_child = fork();
		// todo: exception
		if (!pid_child)
		{
			process_child(data, envp, pipe_a, i);
		}
		else
		{
			process_parent(data, pid_child, pipe_a, i);
		}
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
	{
		printf("argc == %d\n", argc);
		printf("The number of arguments is wrong!\n");
		exit_on_error(&data);
	}
	set_data(&data, argv, envp);
	pipex(&data, envp);

	// test
	//test_anything(envp);
	// todo : free data or exit_free_data
	exit_properly(&data);
	free_data(&data);
	return (0);
}

/*
	Examples


	$> ./pipex infile "ls -l" "wc -l" outfile
	should be the same as “< infile ls -l | wc -l > outfile”

	$> ./pipex infile "grep a1" "wc -w" outfile
	should be the same as “< infile grep a1 | wc -w > outfile”
*/
