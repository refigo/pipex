/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 12:40:15 by mgo               #+#    #+#             */
/*   Updated: 2021/12/18 13:28:58 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// debug
#include <stdio.h>

/*
int	set_buf_cmd(char ***buf_cmd, char **buf_quote, char ***buf_spl, int len_cmd)
{
	char	**buf2_cmd;
	char	len_bufcmd;
	int		i;

	len_bufcmd = ft_strlen((char *)*buf_cmd);
	printf("len_bufcmd == %d\n", len_bufcmd);

	buf2_cmd = ft_calloc(len_cmd + 1, sizeof(char *));
	// todo: exception
	ft_memmove(buf2_cmd, *buf_cmd, len_bufcmd);
	// todo: exception?
	if (*buf_spl)
	{
		i = -1;
		while ((*buf_spl)[++i])
		{
			buf2_cmd[len_bufcmd + i] = ft_strdup((*buf_spl)[i]);
			// todo: exception
		}
		free_2pointer(*buf_spl);
		*buf_spl = NULL;
		free_2pointer(*buf_cmd);
		*buf_cmd = buf2_cmd;
		return (1);
	}
	buf2_cmd[len_cmd] = *buf_quote;
	free(*buf_quote);
	*buf_quote = NULL;
	free_2pointer(*buf_cmd);
	*buf_cmd = buf2_cmd;
	return (1);
}

static void	splitspace_remain(t_pipex *data, int i)
{
	char	**buf_cmd;
	char	*buf_quote;
	char	**buf_spl;
	int		len_cmd;
	int		j;

	buf_cmd = ft_calloc(1, sizeof(char *));
	// todo: exception
	buf_spl = NULL;
	len_cmd = 0;
	j = -1;
	while (data->command[i][++j])
	{
		if (cmd_strset(data->command[i][j], "\'\""))
		{
			buf_quote = ft_strdup(data->command[i][j]);
			// todo: exception
			len_cmd++;
		}
		else
		{
			buf_spl = ft_split(data->command[i][j], ' ');
			// todo: exception
			len_cmd += ft_strlen((char *)buf_spl);
		}
		set_buf_cmd(&buf_cmd, &buf_quote, &buf_spl, len_cmd);
	}
	free_2pointer(data->command[i]);
	data->command[i] = buf_cmd;
}

// split space in pasing quote

*/


// test field
static void	put_splitremain(char ***splitted, char **buf_remain)
{
	char	**buf_splitted;
	int		len_splitted;
	int		i;

	len_splitted = ft_strlen((char *)(*splitted));
	buf_splitted = ft_calloc(len_splitted + ft_strlen((char *)buf_remain) + 1, sizeof(char *));
	// todo: exception
	ft_memmove(buf_splitted, splitted, len_splitted);
	i = -1;
	while (buf_remain[++i])
		buf_splitted[len_splitted + i] = buf_remain[i];
	free_2pointer(buf_remain);
	free_2pointer(*splitted);
	*splitted = buf_splitted;
}

static void	put_quote_cmd(char ***splitted, char *buf_quote)
{
	char	**buf_splitted;
	int		len_splitted;

	len_splitted = ft_strlen((char *)(*splitted));
	buf_splitted = ft_calloc(len_splitted + 2, sizeof(char *));
	// todo: exception
	ft_memmove(buf_splitted, splitted, len_splitted);
	buf_splitted[len_splitted] = buf_quote;
	free_2pointer(*splitted);
	*splitted = buf_splitted;
}

static char	**splitquote_remain(char *src, char quote)
{
	char	**splitted;
	char	**buf_remain;
	char	*buf_quote;
	int		i;

	splitted = ft_calloc(1, sizeof(char *));
	i = -1;
	while (src[++i])
	{
		if (src[i] != quote)
			continue ;	// is right?
		src[i] = '\0';
		buf_remain = ft_split(src, ' ');
		// todo: exception
		buf_quote = &(src[i + 1]);
		while (src[++i] != quote) ; // is right?
		src[i] = '\0';
		buf_quote = ft_strdup(buf_quote);
		// todo: exception

		put_splitremain(&splitted, buf_remain);
		put_quote_cmd(&splitted, buf_quote);
		buf_quote = &src[i + 1];
	}
	buf_remain = ft_split(buf_quote, ' ');
	put_splitremain(&splitted, buf_remain);
	return (splitted);
}
// test field

void	cmd_splitquote(t_pipex *data, char **argv, int i)
{
	//char	*buf_command;
	char	quote_found;
	//int		j;

	quote_found = cmd_strset(argv[2 + i], "\'\"");

	data->command[i] = splitquote_remain(argv[2 + i], quote_found); // making

	/*
	data->command[i] = ft_split(argv[2 + i], quote_found);
	if (!data->command[i])
		exit_on_error(data, strerror(errno), 1);
	j = -1;
	while (data->command[i][++j])
	{
		buf_command = ft_strtrim(data->command[i][j], " ");
		if (!buf_command)
			exit_on_error(data, strerror(errno), 1);
		free(data->command[i][j]);
		data->command[i][j] = buf_command;
	}
	*/
	// splitspace_remain(data, i); // to remove
}

int	cmd_strset(char *str, char *set)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_strchr(set, str[i]))
			return (str[i]);
	return (0);
}

void	free_2pointer(char	**p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
}

void	free_3pointer(char	***p)
{
	int	i;

	i = -1;
	while (p[++i])
		free_2pointer(p[i]);
	free(p);
}
