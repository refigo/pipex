/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quote_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 19:41:50 by mgo               #+#    #+#             */
/*   Updated: 2022/04/14 19:41:54 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	put_quote_cmd(char ***splitted, char *buf_quote)
{
	char	**buf_splitted;
	int		len_splitted;
	int		i;

	len_splitted = find_len2pointer(*splitted);
	buf_splitted = ft_calloc(len_splitted + 2, sizeof(char *));
	if (!buf_splitted)
		return (0);
	i = -1;
	while (++i < len_splitted)
		if (!set_strdup(&(buf_splitted[i]), (*splitted)[i]))
			return (free_2pointer(buf_splitted));
	buf_splitted[len_splitted] = ft_strdup(buf_quote);
	if (!(buf_splitted[i]))
		return (free_2pointer(buf_splitted));
	free(buf_quote);
	free_2pointer(*splitted);
	*splitted = buf_splitted;
	return (1);
}

static int	get_quote_cmd(char ***splitted, char *src_tmp)
{
	char	*buf_quote;

	buf_quote = ft_strdup(src_tmp);
	if (!buf_quote)
		return (0);
	if (!put_quote_cmd(splitted, buf_quote))
	{
		free(buf_quote);
		return (0);
	}
	return (1);
}

static int	parse_quote(char ***splitted, char *src, char quote_found)
{
	char	*src_tmp;
	int		i;

	src_tmp = src;
	i = -1;
	while (src[++i])
	{
		if (src[i] != quote_found)
			continue ;
		src[i] = '\0';
		if (!splitspace_remain(splitted, src_tmp))
			return (0);
		src_tmp = &(src[++i]);
		while (src[i] && src[i] != quote_found)
			i++;
		if (src[i] == '\0')
			return (get_quote_cmd(splitted, src_tmp));
		src[i] = '\0';
		if (!get_quote_cmd(splitted, src_tmp))
			return (0);
		src_tmp = &src[i + 1];
	}
	if (*src_tmp && !splitspace_remain(splitted, src_tmp))
		return (0);
	return (1);
}

char	**cmd_splitquote(char *str_cmd)
{
	char	**ret_splitted;
	char	quote_found;

	quote_found = search_strset(str_cmd, "\'\"");
	ret_splitted = ft_calloc(1, sizeof(char *));
	if (!ret_splitted)
		return (NULL);
	if (!parse_quote(&ret_splitted, str_cmd, quote_found))
	{
		free_2pointer(ret_splitted);
		return (NULL);
	}
	return (ret_splitted);
}
