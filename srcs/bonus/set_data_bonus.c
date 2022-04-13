/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:52:40 by mgo               #+#    #+#             */
/*   Updated: 2022/04/12 12:31:56 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	set_exec(t_pipex *data)
{
	int	i;
	int	j;

	data->exec = (char **)ft_calloc(data->num_cmd + 1, sizeof(char *));
	if (!data->exec)
		exit_perror(data, 1);
	i = -1;
	while (data->command[++i])
	{
		j = -1;
		while (data->path[++j])
		{
			data->exec[i] = ft_strjoin(data->path[j], data->command[i][0]);
			if (!data->exec[i])
				exit_perror(data, 1);
			if (access(data->exec[i], X_OK) == 0)
				break ;
			free(data->exec[i]);
			data->exec[i] = NULL;
		}
		if (!data->exec[i])
			data->exec[i] = ft_strdup(data->command[i][0]);
		if (!data->exec[i])
			exit_perror(data, 1);
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
			exit_perror(data, 1);
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
			exit_perror(data, 1);
		add_slash_to_path(data, data->path);
	}
}

static void	set_command(t_pipex *data, int argc, char **argv)
{
	int	i;

	data->num_cmd = argc - 3;	// todo: considering here_doc
	data->command = (char ***)ft_calloc(data->num_cmd + 1, sizeof(char **));
	if (!data->command)
		exit_perror(data, 1);
	i = -1;
	while (++i < data->num_cmd)
	{
		if (search_strset(argv[2 + i], "\'\""))
			data->command[i] = cmd_splitquote(argv[2 + i]);
		else
			data->command[i] = ft_split(argv[2 + i], ' ');
		if (!data->command[i])
			exit_perror(data, 1);
	}
}

void	set_data(t_pipex *data, int argc, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_pipex));
	data->infile = argv[1];	// todo: check here_doc
	data->outfile = argv[argc - 1];
	set_command(data, argc, argv);
	get_path(data, envp);
	set_exec(data);
}
