/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:49:46 by mgo               #+#    #+#             */
/*   Updated: 2021/12/04 11:49:50 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** =============================================================================
** etc
** =============================================================================
*/

void	exit_free_data(t_pipex *data)
{
	// TODO : free data's pointer properly
	exit(1);
}

/*
** =============================================================================
** test
** =============================================================================
*/

int	test_anything(char **envp)
{
	char *str_array[3] = {"ls", "-l", NULL};
	int	status;

	status = access("/bin/ls", X_OK);
	printf("access status : %d\n", status);
	execve("/bin/ls", str_array, envp);
	return (0);
}

int	test_command_array(char ***command)
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

	i = -1;
	printf("===== test data =====\n");
	printf("infile : [%s]\n", data->infile);
	printf("outfile : [%s]\n", data->outfile);
	printf("<command>\n");
	test_command_array(data->command);
	printf("<path>\n");
	while (data->path[++i])
		printf("[%s]", data->path[i]);
	printf("\n===== complete test data =====\n");
	return (0);
}

/*
** =============================================================================
** set_data.c
** =============================================================================
*/

int	get_path(t_pipex **data, char **envp)
{
	int	i;
	char	**path_buf;

	i = -1;
	while (envp[++i])
		if (ft_strnstr(envp[i], "PATH=", 5))
			break ;
	path_buf = ft_split(envp[i] + 5, ':');
	if (!path_buf)
		exit_free_data(*data);
	(*data)->path = path_buf;
	return (1);
}

int	set_command(t_pipex **data, char **argv)
{
	// TODO : set argv's command to data
	char	***command_buf;

	command_buf = (char ***)ft_calloc(3, sizeof(char **));
	// todo : exception
	command_buf[0] = ft_split(argv[2], ' ');
	// todo : exception
	command_buf[1] = ft_split(argv[3], ' ');
	// todo : exception
	(*data)->command = command_buf;
	return (0);
}

int	set_data(t_pipex **data, char **argv, char **envp)
{
	*data = (t_pipex *)ft_calloc(1, sizeof(t_pipex));
	if (!(*data))
		exit_free_data(*data);
	(*data)->infile = argv[1];
	(*data)->outfile = argv[4];
	set_command(data, argv);
	get_path(data, envp);
	// set_file();

	// test
	test_data(*data);
	return (1);
}

/*
** =============================================================================
** pipex.c
** =============================================================================
*/

int	pipex(int argc, char **argv)
{
	printf("argc == %d\n", argc);
	printf("Inputs are %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*data;

	if (argc != 5)
	{
		printf("argc == %d\n", argc);
		printf("The number of arguments is wrong!\n");
		exit(1);
	}
	set_data(&data, argv, envp);
	pipex(argc, argv);
	test_anything(envp);
	// todo : free data or exit_free_data
	return (0);
}

/*
	Examples


	$> ./pipex infile "ls -l" "wc -l" outfile
	should be the same as “< infile ls -l | wc -l > outfile”

	$> ./pipex infile "grep a1" "wc -w" outfile
	should be the same as “< infile grep a1 | wc -w > outfile”
*/
