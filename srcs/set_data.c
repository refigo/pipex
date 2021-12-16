/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:52:40 by mgo               #+#    #+#             */
/*   Updated: 2021/12/16 11:09:33 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_exec(t_pipex *data)
{
	int	i;
	int	j;

	data->exec = (char **)ft_calloc(3, sizeof(char *));
	if (!data->exec)
		exit_on_error(data, "malloc failed", 0);
	i = -1;
	while (data->command[++i])
	{
		j = -1;
		while (data->path[++j])
		{
			data->exec[i] = ft_strjoin(data->path[j], data->command[i][0]);
			if (!data->exec[i])
				exit_on_error(data, "malloc failed", 0);
			if (!access(data->exec[i], X_OK))
				break ;
			free(data->exec[i]);
			data->exec[i] = 0;
		}
		if (!data->exec[i])
			data->exec[i] = ft_strdup(data->command[i][0]);
		if (!data->exec[i])
			exit_on_error(data, "malloc failed", 0);
	}
}

static void	add_slash_to_path(t_pipex *data, char **path)
{
	char	*buf;
	int		len_path;
	int		i;

	i = -1;
	while (path[++i])
	{
		len_path = ft_strlen(path[i]);
		buf = (char *)ft_calloc(1, len_path + 2);
		if (!buf)
			exit_on_error(data, "malloc failed", 0);
		ft_memmove(buf, path[i], len_path);
		buf[len_path] = '/';
		free(path[i]);
		path[i] = buf;
	}
}

static void	get_path(t_pipex *data, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
	if (envp[i])
	{
		data->path = ft_split(envp[i] + 5, ':');
		if (!data->path)
			exit_on_error(data, "malloc failed", 0);
		add_slash_to_path(data, data->path);
	}
}

int	mgo_strset(char *str, char *set)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_strchr(set, str[i]))
			return (str[i]);
	}
	return (0);
}

int	mgo_splitset(t_pipex *data, char **argv, int i)
{
	char	*buf_command;
	int	j;

	data->command[i] = ft_split(argv[2 + i], mgo_strset(argv[2 + i], "\'\""));
	// todo: exception
	if (!data->command[i])
		exit_on_error(data, "malloc failed", 0);
	j = -1;
	while (data->command[i][++j])
	{
		buf_command = ft_strtrim(data->command[i][j], " ");
		// todo: exception
		if (!buf_command)
			exit_on_error(data, "malloc failed", 0);
		free(data->command[i][j]);
		data->command[i][j] = buf_command;
	}
	return (0);
}

static void	set_command(t_pipex *data, char **argv)
{
	int	num_cmd;
	int	i;

	num_cmd = 2;
	data->command = (char ***)ft_calloc(num_cmd + 1, sizeof(char **));
	if (!data->command)
		exit_on_error(data, "malloc failed", 0);
	i = -1;
	while (++i < num_cmd)
	{
		if (mgo_strset(argv[2 + i], "\'\""))
			mgo_splitset(data, argv, i);
		else
			data->command[i] = ft_split(argv[2 + i], ' ');
		if (!data->command[i])
			exit_on_error(data, "malloc failed", 0);
	}	
}

void	set_data(t_pipex *data, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_pipex));
	data->infile = argv[1];
	data->outfile = argv[4];
	set_command(data, argv);
	get_path(data, envp);
	set_exec(data);
	// test
	test_data(data);
}
