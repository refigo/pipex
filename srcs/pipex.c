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
** etc
** =============================================================================
*/

void	exit_free_data(t_pipex *data)
{
	// TODO : free data's pointer properly
	exit(1);
}

/*
** =============================================================================
** pipex.c
** =============================================================================
*/

int	process_parent(t_pipex **data, int pid_child, int *pipe_a, int i)
{
	int	status;

	if (i == 0)
		close(pipe_a[1]);
	else
		close(pipe_a[0]);
	waitpid(pid_child, &status, 0);
	return (0);
}

int	process_child(t_pipex **data, char **envp, int *pipe_a, int i)
{
	int	fd;

	if (i == 0)
	{
		close(pipe_a[0]);
		fd = open((*data)->infile, O_RDONLY);
		// todo: exception
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(pipe_a[1], STDOUT_FILENO);
		close(pipe_a[1]);
	}
	else
	{
		fd = open((*data)->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// todo: exception
		dup2(pipe_a[0], STDIN_FILENO);
		close(pipe_a[0]);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	execve((*data)->to_exec[i], (*data)->command[i], envp);
	exit(0);
	// todo: free data
	return (0);
}

int	pipex(t_pipex **data, char **envp)
{
	int	pipe_a[2];
	pid_t	pid_child;
	int	i;

	i = -1;
	pipe(pipe_a);
	// todo: exception
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
	t_pipex	*data;

	if (argc != 5)
	{
		printf("argc == %d\n", argc);
		printf("The number of arguments is wrong!\n");
		exit(1);
	}
	set_data(&data, argv, envp);
	pipex(&data, envp);

	// test
	//test_anything(envp);
	// todo : free data or exit_free_data
	return (0);
}

/*
	Examples


	$> ./pipex infile "ls -l" "wc -l" outfile
	should be the same as “< infile ls -l | wc -l > outfile”

	$> ./pipex infile "grep a1" "wc -w" outfile
	should be the same as “< infile grep a1 | wc -w > outfile”
*/
