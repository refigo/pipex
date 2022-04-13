/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:49:46 by mgo               #+#    #+#             */
/*   Updated: 2022/04/12 18:48:33 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// exit_error_argc

static int	pipex(t_pipex *data, char **envp)
{
	int		*pipes;
	pid_t	*pid_child;
	int		status_child;
	int		i;
	// todo: pipe_b

	pid_child = ft_calloc(data->num_cmd, sizeof(pid_t));
	if (!pid_child)
		exit_perror(data, 1);

	pipes = ft_calloc((data->num_cmd - 1) * 2, sizeof(int));
	if (!pipes)
		exit_perror(data, 1);

	
	status_child = 0;
	i = -1;
	while (++i < data->num_cmd)	// todo: change for bonus
	{
		if (i < (data->num_cmd - 1))
			if (set_pipe_with_index(pipes, i) == -1)
				exit_perror(data, 1);

		pid_child[i] = fork();
		if (pid_child[i] == -1)
			exit_perror(data, 1);
		else if (pid_child[i] == 0)
			process_child(data, envp, pipes, i);
		else
			process_parent(data, pid_child[i], pipes, i);
	}

	//printf("waitpid last: [%d]\n", waitpid(pid_child[i], &status_child, 0));
	
	int	check_wpid;
	i = -1;
	while (++i < data->num_cmd)
	{
		check_wpid = waitpid(pid_child[i], &status_child, 0);
		printf("check_wpid: [%d]\n", check_wpid);
	}
	
	free(pid_child);
	free(pipes);
	return (WEXITSTATUS(status_child));
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		ret;

	printf("hello! I'm bonus!\n");
	if (argc < 5)
		exit_error_2msg(NULL, \
		"mgosh: ambiguous redirect(the number of arguments is little)\n", \
		"usage1: ./pipex infile \"cmd1\" \"cmd2\" ... \"cmdn\" outfile\n\
usage2: ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" outfile", 1);
	set_data(&data, argc, argv, envp);

	//test_data(&data);

	//ret = 0;
	//(void)pipex;
	ret = pipex(&data, envp);
	free_data(&data);
	return (ret);
}
