/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:30:14 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 13:20:57 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_perror(t_pipex *data, int code)
{
	perror("mgosh");
	free_data(data);
	if (!code)
		exit(1);
	else
		exit(code);
}

void	exit_on_error(t_pipex *data, char *msg, int code)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	free_data(data);
	if (!code)
		exit(1);
	else
		exit(code);
}
