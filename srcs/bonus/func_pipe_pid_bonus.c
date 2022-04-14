/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pipe_pid_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:42:14 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:42:17 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	calloc_pipes_and_pids(t_pipex *data)
{
	data->pids = ft_calloc(data->num_cmd, sizeof(pid_t));
	if (!(data->pids))
		exit_perror(data, 1);
	data->pipes = ft_calloc((data->num_cmd - 1) * 2, sizeof(int));
	if (!(data->pipes))
		exit_perror(data, 1);
}

int	set_pipe_index(int *pipes, int index)
{
	if (pipe(&(pipes[index * 2])) == -1)
		return (-1);
	return (0);
}

int	get_pipe_index(int *pipes, int index, enum e_pipe ACT)
{
	return (pipes[(index * 2) + ACT]);
}

void	close_pipe_index(int *pipes, int index, enum e_pipe ACT)
{
	close(pipes[(index * 2) + ACT]);
}
