#include "inc/malloc.h"
#include <stdio.h>


int main(int argc, char **argv)
{
	char	*lol;
	int		i;
	void	*lolii;

	i = 0;
	lol = ft_malloc(sizeof(char) * 10);
	ft_malloc(90);
	if (!lol)
	{
		write(1, "malloc return NUll\n", 19);
		return (3);
	}
	while (i < 8)
	{
		lol[i] = 'a';
		i++;
	}
	lol[8] = '\0';
	write(1, lol, 9);
	write(1, "\n", 1);
	write(1, "test free1\n", 11);
	ft_free(lol);
	write(1, "test free2\n", 11);
	ft_free(lolii);
	return (1);
}
