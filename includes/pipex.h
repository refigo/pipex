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
** free.c
** =============================================================================
*/

void	free_data(t_pipex *data);

/*
** =============================================================================
** exit.c
** =============================================================================
*/

void	exit_on_error(t_pipex *data, char *msg);
void	exit_properly(t_pipex *data);

/*
** =============================================================================
** set_data.c
** =============================================================================
*/

int	set_data(t_pipex *data, char **argv, char **envp);

/*
** =============================================================================
** test.c
** =============================================================================
*/
int	test_anything(char **envp);
int	test_command_array(char ***command);
int	test_data(t_pipex *data);

#endif