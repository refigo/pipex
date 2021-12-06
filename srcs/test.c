
#include "pipex.h"

/*
** =============================================================================
** test
** =============================================================================
*/

int	test_anything(char **envp)
{
	char *str_array[3] = {"ls", "-l", NULL};
	int	status;

	status = access("/bin/ls", X_OK);
	printf("access status : %d\n", status);
	execve("/bin/ls", str_array, envp);
	return (0);
}

int	test_command_array(char ***command)
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
	printf("\n<file>\n");
	i = -1;
	while (data->file[++i])
		printf("[%s]\n", data->file[i]);
	printf("===== complete test data =====\n");
	return (0);
}
