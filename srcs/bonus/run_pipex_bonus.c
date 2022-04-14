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

static void	calloc_pipes_and_pids(t_pipex *data, int **pipes, pid_t **pids)
{
	*pids = ft_calloc(data->num_cmd, sizeof(pid_t));
	if (!(*pids))
		exit_perror(data, 1);
	*pipes = ft_calloc((data->num_cmd - 1) * 2, sizeof(int));
	if (!(*pipes))
		exit_perror(data, 1);
}

static void	set_pipe_and_run_cmd(t_pipex *data, char **envp, \
									int *pipes, pid_t *pid_childs, int i)
{
	if (i < (data->num_cmd - 1))
		if (set_pipe_index(pipes, i) == -1)
			exit_perror(data, 1);
	pid_childs[i] = fork();
	if (pid_childs[i] == -1)
		exit_perror(data, 1);
	else if (pid_childs[i] == 0)
		process_child(data, envp, pipes, i);
	else
		process_parent(data, pipes, i);
}

int	run_pipex(t_pipex *data, char **envp)
{
	int		*pipes;
	pid_t	*pid_childs;
	int		status_child;
	int		i;

	calloc_pipes_and_pids(data, &pipes, &pid_childs); // to set_data?
	status_child = 0;
	i = -1;
	while (++i < data->num_cmd)
		set_pipe_and_run_cmd(data, envp, pipes, pid_childs, i);
	i = -1;
	while (++i < data->num_cmd)
		waitpid(pid_childs[i], &status_child, 0);
	free(pid_childs);
	free(pipes);
	return (WEXITSTATUS(status_child));
}
