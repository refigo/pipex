/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:30:14 by mgo               #+#    #+#             */
/*   Updated: 2021/12/16 11:09:48 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
