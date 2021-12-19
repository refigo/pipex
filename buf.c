
#include "pipex.h"

// debug
#include <stdio.h>

static void	put_splitremain(char ***splitted, char **buf_remain)
{
	char	**buf_splitted;
	int		len_splitted;
	int		i;

	len_splitted = ft_strlen((char *)(*splitted));
	buf_splitted = ft_calloc(len_splitted + ft_strlen((char *)buf_remain) + 1, sizeof(char *));
	// todo: exception
	i = -1;
	while (++i < len_splitted)
		buf_splitted[i] = ft_strdup((*splitted)[i]);
		// todo: exception
	i = -1;
	while (buf_remain[++i])
		buf_splitted[len_splitted + i] = ft_strdup(buf_remain[i]);
		// todo: exception
	free_2pointer(buf_remain);
	free_2pointer(*splitted);
	*splitted = buf_splitted;
}

static void	put_quote_cmd(char ***splitted, char *buf_quote)
{
	char	**buf_splitted;
	int		len_splitted;
	int		i;

	//len_splitted = ft_strlen((char *)(*splitted));
	len_splitted = 0;
	while ((*splitted)[len_splitted] != NULL)
		len_splitted++;
	buf_splitted = ft_calloc(len_splitted + 2, sizeof(char *));
	// todo: exception	
	i = -1;
	while (++i < len_splitted)
	{
		buf_splitted[i] = ft_strdup((*splitted)[i]);
		// todo: exception
	}
	buf_splitted[len_splitted] = ft_strdup(buf_quote);
	free(buf_quote);
	free_2pointer(*splitted);
	*splitted = buf_splitted;
}

static char	**splitquote_remain(char *src, char quote_found)
{
	char	**splitted;
	char	**buf_remain;
	char	*buf_quote;
	char	*buf_src;
	int		i;

	splitted = ft_calloc(1, sizeof(char *));
	// todo: exception
	buf_src = src;
	i = -1;
	while (src[++i])
	{
		if (src[i] != quote_found)
			continue ;	// is right?
		src[i] = '\0';
		buf_remain = ft_split(buf_src, ' ');
		// todo: exception
		buf_quote = &(src[++i]);
		while (src[i] != quote_found)
			i++; // is right?
		src[i] = '\0';
		buf_quote = ft_strdup(buf_quote);
		// todo: exception
		put_splitremain(&splitted, buf_remain);
		put_quote_cmd(&splitted, buf_quote);
		buf_src = &src[i + 1];
	}
	buf_remain = ft_split(buf_src, ' ');
	// todo: exception
	put_splitremain(&splitted, buf_remain);
	return (splitted);
}

void	cmd_splitquote(t_pipex *data, char **argv, int i)
{
	char	quote_found;

	quote_found = cmd_strset(argv[2 + i], "\'\"");
	data->command[i] = splitquote_remain(argv[2 + i], quote_found);
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
