
#include "pipex_bonus.h"

int	set_pipe_with_index(int *pipes, int index)
{
	if (pipe(&(pipes[index * 2])) == -1)
		return (-1);
	return (0);
}

int	get_pipe_index(int *pipes, int index, enum e_pipe ACT)
{
	return (pipes[(index * 2) + ACT]);
}

void	close_pipe_index(int *pipes, int index, enum e_pipe ACT)
{
	close(pipes[(index * 2) + ACT]);
}
