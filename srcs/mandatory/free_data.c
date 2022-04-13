/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:30:03 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 13:21:09 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_data(t_pipex *data)
{
	free_command(data);
	free_path(data);
	free_exec(data);
}
