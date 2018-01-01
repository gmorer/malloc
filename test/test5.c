#include <stdlib.h>
#include <unistd.h>
#include "../inc/malloc.h"

void	show_alloc_mem(void);

int main(void)
{
	write(1, "--0--\n", 6);
	malloc(10);
	write(1, "--1--\n", 6);
	malloc(1024 * 32);
	write(1, "--2--\n", 6);
	malloc(1024 * 1024);
	write(1, "--3--\n", 6);
	malloc(1024 * 1024 * 16);
	write(1, "--4--\n", 6);
	malloc(1024 * 1024 * 128);
	write(1, "--5--\n", 6);
	show_alloc_mem();
	return (0);
}
