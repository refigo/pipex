#include "libft.h"

int	mgo_free_2ptr(char	**p)
{
	int	i;

	i = -1;
	while (p[++i])
		free(p[i]);
	free(p);
	return (0);
}

int	mgo_free_3ptr(char	***p)
{
	int	i;

	i = -1;
	while (p[++i])
		mgo_free_2ptr(p[i]);
	free(p);
	return (0);
}
