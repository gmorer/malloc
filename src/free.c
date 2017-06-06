#include "malloc.c"

void	free(void *ptr)
{
	munmap(ptr, 4);
}
