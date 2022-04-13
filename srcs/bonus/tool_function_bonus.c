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

int	set_strdup(char **dest, char *src)
{
	*dest = ft_strdup(src);
	if (!(*dest))
		return (0);
	return (1);
}

int	search_strset(char *str, char *set)
{
	int	i;

	i = -1;
	while (str[++i])
		if (ft_strchr(set, str[i]))
			return (str[i]);
	return (0);
}

int	find_len2pointer(char **p)
{
	int	len;

	len = 0;
	while (*p)
	{
		p++;
		len++;
	}
	return (len);
}

int	free_2pointer(char	**p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
	return (0);
}

int	free_3pointer(char	***p)
{
	int	i;

	i = -1;
	while (p[++i])
		free_2pointer(p[i]);
	free(p);
	return (0);
}
