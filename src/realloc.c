#include "malloc.h"

void	*realloc(void *ptr, size_t len)
{
	free(ptr);
	return (malloc(len));
}
