#include "malloc.h"
#include <stdio.h>

t_zone		*g_base;

void show_alloc_mem()
{
	t_zone			*zone_tmp;
	t_block			*block_tmp;
	unsigned int	total;

	zone_tmp = g_base;
	total = 0;
	while (zone_tmp)
	{
		if (zone_tmp->size == TINY - sizeof(t_zone))
			printf("TINY : %p\n", (void*)((t_zone*)zone_tmp + 1));
		else if (zone_tmp->size == SMALL - sizeof(t_zone))
			printf("SMALL : %p\n", (void*)((t_zone*)zone_tmp + 1));
		else
			printf("LARGE : %p\n", (void*)((t_zone*)zone_tmp + 1));
		block_tmp = (void*)((t_zone*)zone_tmp + 1);
		while(block_tmp)
		{
			printf("%p - %p : %zu octets\n", (void*)((t_block*)block_tmp + 1),
					(void*)((t_block*)block_tmp + 1) + block_tmp->size,
					(void*)((t_block*)block_tmp + 1) + block_tmp->size - (void*)((t_block*)block_tmp + 1));
			total += (void*)((t_block*)block_tmp + 1) + block_tmp->size - (void*)((t_block*)block_tmp + 1);
			block_tmp = block_tmp->next;
		}
		zone_tmp = zone_tmp->next;
	}
	printf("Total : %u\n", total);
	write(1, "lol\n", 4);
	return ;
}
