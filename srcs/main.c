/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:49:46 by mgo               #+#    #+#             */
/*   Updated: 2021/12/16 11:09:06 by mgo              ###   ########.fr       */
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
		exit_on_error(data, "pipe failed", 0);
	status_child = 0;
	i = -1;
	while (++i < 2)
	{
		pid_child = fork();
		if (pid_child == -1)
			exit_on_error(data, strerror(errno), 0);
		else if (!pid_child)
			process_child(data, envp, pipe_a, i);
		else
			process_parent(&status_child, pid_child, pipe_a, i);
	}
	waitpid(pid_child, &status_child, 0);
	return (WEXITSTATUS(status_child));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		ret;

	if (argc != 5)
	{
		ft_putendl_fd("The number of arguments is wrong!", 2);
		ft_putendl_fd("usage: infile \"cmd1\" \"cmd2\" outfile", 2);
		return (1);
	}
	set_data(&data, argv, envp);
	ret = pipex(&data, envp);
	free_data(&data);
	return (ret);
}
