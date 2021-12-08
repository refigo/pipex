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

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "libft.h"

/*
** =============================================================================
** Struct
** =============================================================================
*/

typedef struct  s_pipex
{
    char    *infile;
    char    *outfile;
    char    ***command;
    char    **path;
    char    **exec;
}               t_pipex;

/*
** =============================================================================
** Macro
** =============================================================================
*/

# ifndef OPEN_MAX
#  define OPEN_MAX  4096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE   4096
#endif

/*
** =============================================================================
** Functions
** =============================================================================
*/

// set_data.c
void	set_data(t_pipex *data, char **argv, char **envp);

// free_data.c
void	free_data(t_pipex *data);

// exit.c
void	exit_on_error(t_pipex *data, char *msg);
void	exit_properly(t_pipex *data);

// process.c
int	process_parent(t_pipex *data, int pid_child, int *pipe_a, int i);
void	process_child(t_pipex *data, char **envp, int *pipe_a, int i);

// test.c
int	test_anything(char **envp);
int	test_command_array(char ***command);
int	test_data(t_pipex *data);

#endif