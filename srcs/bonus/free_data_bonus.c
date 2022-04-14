/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:41:44 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:41:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_command(t_pipex *data)
{
	if (data->command)
		free_3pointer(data->command);
	data->command = NULL;
}

static void	free_path(t_pipex *data)
{
	if (data->path)
		free_2pointer(data->path);
	data->path = NULL;
}

static void	free_exec(t_pipex *data)
{
	if (data->exec)
		free_2pointer(data->exec);
	data->exec = NULL;
}

static void	free_pipes_and_pids(t_pipex *data)
{
	if (data->pipes)
		free(data->pipes);
	if (data->pids)
		free(data->pids);
}

void	free_data(t_pipex *data)
{
	free_command(data);
	free_path(data);
	free_exec(data);
	free_pipes_and_pids(data);
	if (!ft_strncmp(data->infile, ".here_doc", ft_strlen(".here_doc") + 1))
		unlink(data->infile);
}
