/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipex_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 13:30:46 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 13:30:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	set_pipe_and_run_cmd(t_pipex *data, char **envp, int i)
{
	if (i < (data->num_cmd - 1))
		if (set_pipe_index(data->pipes, i) == -1)
			exit_perror(data, 1);
	(data->pids)[i] = fork();
	if ((data->pids)[i] == -1)
		exit_perror(data, 1);
	else if ((data->pids)[i] == 0)
		process_child(data, envp, i);
	else
		process_parent(data, i);
}

int	run_pipex(t_pipex *data, char **envp)
{
	int		status_child;
	int		i;

	status_child = 0;
	i = -1;
	while (++i < data->num_cmd)
		set_pipe_and_run_cmd(data, envp, i);
	i = -1;
	while (++i < data->num_cmd)
		waitpid(data->pids[i], &status_child, 0);
	return (WEXITSTATUS(status_child));
}
