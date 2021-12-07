/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:52:40 by mgo               #+#    #+#             */
/*   Updated: 2021/12/06 16:52:41 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** =============================================================================
** set_data.c
** =============================================================================
*/

static int	set_exec(t_pipex *data)
{
	char	**exec_buf;
	int	i;
	int	j;

	exec_buf = (char **)ft_calloc(3, sizeof(char *));
	// todo : exception
	i = -1;
	while (data->command[++i])
	{
		j = -1;
		while (data->path[++j])
		{
			exec_buf[i] = ft_strjoin(data->path[j], data->command[i][0]);
			// todo : exception
			if (!access(exec_buf[i], X_OK))
				break ;
			free(exec_buf[i]);
		}
	}
	data->exec = exec_buf;
	return (0);
}

static int	add_slash_to_path(char **path)
{
	char	*buf;
	int	len_path;
	int	i;

	i = -1;
	while (path[++i])
	{
		len_path = ft_strlen(path[i]);
		buf = (char *)ft_calloc(1, len_path + 2);
		buf = ft_memmove(buf, path[i], len_path);
		// todo : exception
		buf[len_path] = '/';
		free(path[i]);
		path[i] = buf;
	}
	return (0);
}

static int	get_path(t_pipex *data, char **envp)
{
	int	i;
	char	**path_buf;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
	path_buf = ft_split(envp[i] + 5, ':');
	// todo : exception
	if (!path_buf)
		exit_free_data(data);
	i = -1;
	add_slash_to_path(path_buf);
	data->path = path_buf;
	return (1);
}

static int	set_command(t_pipex *data, char **argv)
{
	char	***command_buf;

	command_buf = (char ***)ft_calloc(3, sizeof(char **));
	// todo : exception
	command_buf[0] = ft_split(argv[2], ' ');
	// todo : exception
	command_buf[1] = ft_split(argv[3], ' ');
	// todo : exception
	data->command = command_buf;
	return (0);
}

int	set_data(t_pipex *data, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_pipex));
	data->infile = argv[1];
	data->outfile = argv[4];
	set_command(data, argv);
	get_path(data, envp);
	set_exec(data);

	// test
	test_data(data);
	return (1);
}
