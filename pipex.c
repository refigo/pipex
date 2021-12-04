#include "pipex.h"

int	pipex(char **argv)
{
	printf("Inputs are %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
	return (0);
}

void	exit_custom(int argc)
{
	printf("argc == %d\n", argc);
	printf("The number of arguments is wrong!\n");
	exit(1);
}



int	set_command(char **envp)
{
	int	i;

	// get path
	i = 0;
}

int	main(int argc, char **argv, char **envp)
{
	int	i;

	/*
	i = -1;
	while (envp[++i])
		printf("envp%d -> %s\n", i, envp[i]);
	i = 1;
	printf("argc == %d\n", argc);
	printf("Inputs are\n");
	while (i < argc)
	{
		printf("%s ", argv[i++]);
	}
	printf("\n");
	*/
	if (argc != 5)
	{
		exit_custom(argc);
	}
	set_command(envp);
	printf("argc == %d\n", argc);
	pipex(argv);
	return (0);
}

/*
	Examples

	$> ./pipex infile ``ls -l'' ``wc -l'' outfile
	should be the same as “< infile ls -l | wc -l > outfile”

	$> ./pipex infile ``grep a1'' ``wc -w'' outfile
	should be the same as “< infile grep a1 | wc -w > outfile”
*/
