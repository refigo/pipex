/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:43:05 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:43:09 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exit_error_few_args(void)
{
	exit_error_2msg(NULL, \
	"mgosh: ambiguous redirect(the number of arguments is little)\n", \
	"usage1: ./pipex infile \"cmd1\" \"cmd2\" ... \"cmdn\" outfile\n\
	usage2: ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" outfile", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	data;
	int		ret;

	if (argc < 5)
		exit_error_few_args();
	set_data(&data, argc, argv, envp);
	ret = run_pipex(&data, envp);
	free_data(&data);
	return (ret);
}
