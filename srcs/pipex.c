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

	// test
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
