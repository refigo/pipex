/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:49:46 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 13:21:14 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	pipex(t_pipex *data, char **envp)
{
	int		pipe_a[2];
	pid_t	pid_child;
	int		status_child;
	int		i;

	if (pipe(pipe_a) == -1)
		exit_perror(data, 1);
	status_child = 0;
	i = -1;
	while (++i < 2)
	{
		pid_child = fork();
		if (pid_child == -1)
			exit_perror(data, 1);
		else if (!pid_child)
			process_child(data, envp, pipe_a, i);
		else
			process_parent(pid_child, pipe_a, i);
	}
	waitpid(pid_child, &status_child, 0);
	return (WEXITSTATUS(status_child));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		ret;

	if (argc != 5)
		exit_error_2msg(NULL, \
		"mgosh: ambiguous redirect(the number of arguments is wrong)\n", \
		"usage: ./pipex infile \"cmd1\" \"cmd2\" outfile", 1);
	set_data(&data, argv, envp);
	ret = pipex(&data, envp);
	free_data(&data);
	return (ret);
}
