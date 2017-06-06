#ifndef MALLOC_H
# define MALLOC_H

# include <sys/mman.h>

void		free(void *ptr);
void		*realloc(void *ptr, size_t size);
void		*malloc(size_t size);

#endif
