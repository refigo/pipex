/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:36:02 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:36:10 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exit_error_few_args_with_heredoc(void)
{
	exit_error_2msg(NULL, \
	"mgosh: ambiguous redirect(here_doc: the number of arguments is little)\n", \
	"Usage(here_doc): ./pipex here_doc LIMITER \"cmd1\" \"cmd2\" outfile", 1);
}

void	confirm_heredoc_shifting_sequence(t_pipex *data, \
											int *argc, char ***argv)
{
	if ((*argc) < 6)
		exit_error_few_args_with_heredoc();
	data->is_heredoc = TRUE;
	(*argc)--;
	(*argv)++;
}

static int	write_input_to_heredoc(t_pipex *data, int fd_heredoc)
{
	char	*input_line;
	int		is_limiter;
	int		i;

	is_limiter = FALSE;
	while (is_limiter == FALSE)
	{
		i = -1;
		while (++i < (data->num_cmd - 1))
			ft_putstr_fd("pipe ", STDOUT_FILENO);
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		if (get_next_line(STDIN_FILENO, &input_line) == -1)
			exit_perror(data, 1);
		if (!ft_strncmp(input_line, data->limiter, \
				ft_strlen(data->limiter) + 1))
			is_limiter = TRUE;
		if (is_limiter == FALSE)
			ft_putendl_fd(input_line, fd_heredoc);
		free(input_line);
	}
	return (1);
}

void	set_heredoc_as_infile_and_input(t_pipex *data, char **argv)
{
	int	fd_heredoc;

	data->limiter = argv[1];
	fd_heredoc = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_heredoc == -1)
		exit_perror(data, 1);
	data->infile = ".here_doc";
	write_input_to_heredoc(data, fd_heredoc);
	close(fd_heredoc);
}
