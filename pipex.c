#include <stdio.h>

int	pipex(char **argv)
{
	printf("Inputs are %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	i;

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
	/*
	if (argc == 5)
	{
		printf("argc == %d\n", argc);
		pipex(argv);
	}
	else
	{
		printf("argc == %d\n", argc);
		printf("The number of inputs is wrong!\n");
	}
	*/
	return (0);
}

/*
Examples

$> ./pipex infile ``ls -l'' ``wc -l'' outfile
should be the same as “< infile ls -l | wc -l > outfile”

$> ./pipex infile ``grep a1'' ``wc -w'' outfile
should be the same as “< infile grep a1 | wc -w > outfile”
*/
