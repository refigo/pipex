/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:30:14 by mgo               #+#    #+#             */
/*   Updated: 2021/12/08 19:30:15 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_on_error(t_pipex *data, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	free_data(data);
	exit(1);
}

void	exit_properly(t_pipex *data)
{
	free_data(data);
	exit(0);
}
