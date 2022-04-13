/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_function_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:49:27 by mgo               #+#    #+#             */
/*   Updated: 2022/04/13 20:49:31 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
