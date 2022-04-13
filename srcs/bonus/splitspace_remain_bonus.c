/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitspace_remain.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 13:09:44 by mgo               #+#    #+#             */
/*   Updated: 2021/12/21 13:09:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	put_splitremain(char ***splitted, char **buf_remain)
{
	char	**buf_splitted;
	int		len_splitted;
	int		i;

	len_splitted = find_len2pointer(*splitted);
	buf_splitted = ft_calloc(\
					len_splitted + find_len2pointer(buf_remain) + 1, \
					sizeof(char *));
	if (!buf_splitted)
		return (0);
	i = -1;
	while (++i < len_splitted)
		if (!set_strdup(&(buf_splitted[i]), (*splitted)[i]))
			return (free_2pointer(buf_splitted));
	i = -1;
	while (buf_remain[++i])
		if (!set_strdup(&(buf_splitted[len_splitted + i]), buf_remain[i]))
			return (free_2pointer(buf_splitted));
	free_2pointer(buf_remain);
	free_2pointer(*splitted);
	*splitted = buf_splitted;
	return (1);
}

int	splitspace_remain(char ***splitted, char *src_tmp)
{
	char	**buf_remain;

	buf_remain = ft_split(src_tmp, ' ');
	if (!buf_remain)
		return (0);
	if (!put_splitremain(splitted, buf_remain))
		return (free_2pointer(buf_remain));
	return (1);
}
