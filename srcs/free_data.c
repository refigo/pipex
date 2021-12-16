/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:30:03 by mgo               #+#    #+#             */
/*   Updated: 2021/12/16 11:09:39 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	}
	data->command = NULL;
}

static void	free_path(t_pipex *data)
{
	int	i;

	if (data->path)
	{
		i = -1;
		while (data->path[++i])
			free(data->path[i]);
		free(data->path);
	}
	data->path = NULL;
}

static void	free_exec(t_pipex *data)
{
	int	i;

	if (data->exec)
	{
		i = -1;
		while (data->exec[++i])
			free(data->exec[i]);
		free(data->exec);
	}
	data->exec = NULL;
}

void	free_data(t_pipex *data)
{
	free_command(data);
	free_path(data);
	free_exec(data);
}
