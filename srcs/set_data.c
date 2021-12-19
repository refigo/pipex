/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:52:40 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 13:28:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// for test


// for test data
#include <stdio.h>

static int	test_command_array(char ***command)
{
	int	i;
	int	j;

	i = -1;
	while (command[++i])
	{
		j = -1;
		printf("command %d : ", i + 1);
		while (command[i][++j])
		{
			printf("[%s]", command[i][j]);
		}
		printf("\n");
	}
	return (0);
}

int	test_data(t_pipex *data)
{
	int	i;

	printf("===== test data =====\n");
	printf("infile : [%s]\n", data->infile);
	printf("outfile : [%s]\n", data->outfile);
	printf("<command>\n");
	test_command_array(data->command);
	printf("<path>\n");
	i = -1;
	while (data->path[++i])
		printf("[%s]", data->path[i]);
	printf("\n<to_exec>\n");
	i = -1;
	while (data->exec[++i])
		printf("[%s]\n", data->exec[i]);
	printf("===== complete test data =====\n");
	return (0);
}


// for test

static void	set_exec(t_pipex *data)
{
	int	i;
	int	j;

	data->exec = (char **)ft_calloc(3, sizeof(char *));
	if (!data->exec)
		exit_on_error(data, strerror(errno), 1);
	i = -1;
	while (data->command[++i])
	{
		j = -1;
		while (data->path[++j])
		{
			data->exec[i] = ft_strjoin(data->path[j], data->command[i][0]);
			if (!data->exec[i])
				exit_on_error(data, strerror(errno), 1);
			if (access(data->exec[i], X_OK) == 0)
				break ;
			free(data->exec[i]);
			data->exec[i] = NULL;
		}
		if (!data->exec[i])
			data->exec[i] = ft_strdup(data->command[i][0]);
		if (!data->exec[i])
			exit_on_error(data, strerror(errno), 1);
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
			exit_on_error(data, strerror(errno), 1);
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
			exit_on_error(data, strerror(errno), 1);
		add_slash_to_path(data, data->path);
	}
}

static void	set_command(t_pipex *data, char **argv)
{
	int	num_cmd;
	int	i;

	num_cmd = 2;
	data->command = (char ***)ft_calloc(num_cmd + 1, sizeof(char **));
	if (!data->command)
		exit_on_error(data, strerror(errno), 1);
	i = -1;
	while (++i < num_cmd)
	{
		if (cmd_strset(argv[2 + i], "\'\""))
			cmd_splitquote(data, argv, i);
		else
			data->command[i] = ft_split(argv[2 + i], ' ');
		if (!data->command[i])
			exit_on_error(data, strerror(errno), 1);
	}
}

void	set_data(t_pipex *data, char **argv, char **envp)
{
	ft_memset(data, 0, sizeof(t_pipex));
	data->infile = argv[1];
	data->outfile = argv[4];
	set_command(data, argv);
	get_path(data, envp);


	// test
	test_data(data);

	set_exec(data);

	// test
	test_data(data);
}
