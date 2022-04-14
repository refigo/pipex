/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:48:36 by mgo               #+#    #+#             */
/*   Updated: 2022/04/13 20:48:40 by mgo              ###   ########.fr       */
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

void	free_data(t_pipex *data)
{
	free_command(data);
	free_path(data);
	free_exec(data);
	// todo: unlink heredoc
	if (data->is_heredoc)
		unlink(data->infile);
}
