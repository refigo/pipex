/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:40:15 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 12:40:16 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cmd_strset(char *str, char *set)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_strchr(set, str[i]))
			return (str[i]);
	return (0);
}

void	cmd_splitquote(t_pipex *data, char **argv, int i)
{
	char	*buf_command;
	char	quote_found;
	int		j;

	quote_found = cmd_strset(argv[2 + i], "\'\"");
	data->command[i] = ft_split(argv[2 + i], quote_found);
	if (!data->command[i])
		exit_on_error(data, strerror(errno), 1);
	j = -1;
	while (data->command[i][++j])
	{
		buf_command = ft_strtrim(data->command[i][j], " ");
		if (!buf_command)
			exit_on_error(data, strerror(errno), 1);
		free(data->command[i][j]);
		data->command[i][j] = buf_command;
	}
}

void free_2pointer(void	**p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
}

void free_3pointer(void	***p)
{
	int	i;

	i = -1;
	while (p[++i])
		free_2pointer(p[i]);
	free(p);
}
