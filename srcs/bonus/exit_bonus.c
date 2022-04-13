/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:48:19 by mgo               #+#    #+#             */
/*   Updated: 2022/04/13 20:48:25 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_perror(t_pipex *data, int code_err)
{
	perror("mgosh");
	if (data)
		free_data(data);
	if (!code_err)
		exit(1);
	else
		exit(code_err);
}

void	exit_error_2msg(t_pipex *data, char *msg1, char *msg2, int code_err)
{
	if (msg1)
		ft_putstr_fd(msg1, 2);
	if (msg2)
		ft_putendl_fd(msg2, 2);
	if (data)
		free_data(data);
	if (!code_err)
		exit(1);
	else
		exit(code_err);
}
