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

static void	pipex(t_pipex *data, char **envp)
{
	int		pipe_a[2];
	pid_t	pid_child;
	int		i;

	if (pipe(pipe_a) == -1)
		exit_on_error(data, "pipe failed");
	i = -1;
	while (++i < 2)
	{
		pid_child = fork();
		if (pid_child == -1)
			exit_on_error(data, strerror(errno));
		else if (!pid_child)
			process_child(data, envp, pipe_a, i);
		else
			process_parent(data, pid_child, pipe_a, i);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;

	if (argc != 5)
	{
		ft_putendl_fd("The number of arguments is wrong!", 2);
		ft_putendl_fd("usage: infile \"cmd1\" \"cmd2\" outfile", 2);
		return (1);
	}
	set_data(&data, argv, envp);
	pipex(&data, envp);
	free_data(&data);
	return (0);
}

/*
	Examples


	$> ./pipex infile "ls -l" "wc -l" outfile
	should be the same as “< infile ls -l | wc -l > outfile”

	$> ./pipex infile "grep a1" "wc -w" outfile
	should be the same as “< infile grep a1 | wc -w > outfile”

	https://github.com/vfurmane/pipex-tester
*/
