#include "pipex.h"

// for test data
#include <stdio.h>

static int	test_command_array(char ***command)
{
	int	i;
	int	j;

	i = -1;
	while (command[++i])
	{
		j = -1;
		printf("command %d : ", i + 1);
		while (command[i][++j])
		{
			printf("[%s]", command[i][j]);
		}
		printf("\n");
	}
	return (0);
}

int	test_data(t_pipex *data)
{
	int	i;

	printf("===== test data =====\n");
	printf("infile : [%s]\n", data->infile);
	printf("outfile : [%s]\n", data->outfile);
	printf("<command>\n");
	test_command_array(data->command);
	printf("<path>\n");
	i = -1;
	while (data->path[++i])
		printf("[%s]", data->path[i]);
	printf("\n<to_exec>\n");
	i = -1;
	while (data->exec[++i])
		printf("[%s]\n", data->exec[i]);
	printf("===== complete test data =====\n");
	return (0);
}

// buffer
static void	cmd_splitquote(t_pipex *data, char **argv, int i)
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

