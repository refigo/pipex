/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:50:06 by mgo               #+#    #+#             */
/*   Updated: 2021/12/04 11:50:08 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft.h"
# include <stdio.h> // test

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

enum	e_pipe
{
	READ,
	WRITE
};

typedef struct	s_pipex
{
    char	*infile;
    char	*outfile;
    char	***command;
    char	**path;
    char	**exec;
}				t_pipex;

// set_data.c
void	set_data(t_pipex *data, char **argv, char **envp);

// process.c
void	process_parent(int *status_child, int pid_child, int *pipe_a, int i);
void	process_child(t_pipex *data, char **envp, int *pipe_a, int i);

// free_data.c
void	free_data(t_pipex *data);

// exit.c
void	exit_on_error(t_pipex *data, char *msg, int code);
void	exit_properly(t_pipex *data);

int	test_data(t_pipex *data);

#endif