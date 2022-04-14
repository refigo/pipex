/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:48:44 by mgo               #+#    #+#             */
/*   Updated: 2022/04/13 20:48:48 by mgo              ###   ########.fr       */
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


/*
int	set_heredoc_shifting_sequence(t_pipex *data, int *argc, char ***argv)
{
	int	fd_heredoc;

	data->infile = (*argv)[1];
	return (1);

	// exception for arg num with here_doc
	// ex. arg num is only 4 with here_cod
	// ./pipex here_doc LIMITER cmd0 outfile
	if ((*argc) < 6)
		exit_error_2msg(NULL, "argc is few", "Usage as here_doc", 1); // todo: set error msg
	data->is_heredoc = TRUE;
	data->limiter = (*argv)[2];

	// open(.here_doc)
	fd_heredoc = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_heredoc == -1)
		exit_perror(data, 1);

	// write
	//write_input_to_heredoc(data, fd_heredoc);

	// set infile
	data->infile = ".here_doc";
	(*argc)--;
	(*argv)++;
	return (TRUE);
}
*/

// heredoc_bonus.c

void	check_is_heredoc_shifting_sequence(t_pipex *data, int *argc, char ***argv)
{
	if ((*argc) < 6)
		exit_error_2msg(NULL, "argc is few", "Usage as here_doc", 1); // todo: set error msg
	data->is_heredoc = TRUE;
	(*argc)--;
	(*argv)++;
}


int	write_input_to_heredoc(t_pipex *data, int fd_heredoc)
{
	char	*line;
	int		gnl;
	int		is_limiter;
	int		i;

	//line = NULL;	// should?
	is_limiter = FALSE;
	while (is_limiter == FALSE)
	{
		i = -1;
		while (++i < (data->num_cmd - 1))
			ft_putstr_fd("pipe ", STDOUT_FILENO);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		gnl = get_next_line(STDIN_FILENO, &line); // error handling
		printf("gnl: [%d]\n", gnl);
		if (gnl == -1)
			exit_perror(data, 1);	// with unlink
		if (!ft_strncmp(line, data->limiter, ft_strlen(data->limiter) + 1))
			is_limiter = TRUE;
		if (is_limiter == FALSE)
			ft_putendl_fd(line, fd_heredoc);
		free(line);
		//line = NULL;	// should?
	}
	return (1);
}


void	set_heredoc_as_infile(t_pipex *data, char **argv)
{
	int	fd_heredoc;

	data->limiter = argv[1];

	// open(.here_doc)
	fd_heredoc = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_heredoc == -1)
		exit_perror(data, 1);

	// write
	write_input_to_heredoc(data, fd_heredoc);

	data->infile = ".here_doc";
}


void	set_data(t_pipex *data, int argc, char **argv, char **envp)
{
	int	check_cmp;

	ft_memset(data, 0, sizeof(t_pipex));

	check_cmp = 0;
	check_cmp = ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc") + 1);
	printf("check_cmp: [%d]\n", check_cmp);
	if (check_cmp == 0)
	{
		check_is_heredoc_shifting_sequence(data, &argc, &argv);
		//set_heredoc_shifting_sequence(data, &argc, &argv);
	}
	else
		data->infile = argv[1];	// todo: check here_doc
	data->outfile = argv[argc - 1];

	set_command(data, argc, argv);
	get_path(data, envp);
	set_exec(data);

	if (data->is_heredoc == TRUE)
		set_heredoc_as_infile(data, argv);
	else
		data->infile = argv[1];
	data->outfile = argv[argc - 1];
}
