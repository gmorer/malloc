/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_elem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:40:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/10/07 07:04:19 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		*new_block(void *addr, size_t size, t_zone *zone, t_block *prev)
{
	t_block *block;

	printf("new block at %p and malloc zone start at%p\n", addr, addr + sizeof(t_block));
	block = addr;
	block->size = size;
	block->free = 0;
	block->zone = zone;
	block->prev = prev;
	if (prev)
		prev->next = block;
	zone->use_space += size + sizeof(t_block); 
	block->next = (void*)0;
	return (addr + sizeof(t_block));
}

/* 
** new_zone = looking at space aivability with size + zone size + block size
** if yes :
**  Creat TINY SMALL or cuustom zone;
**  Creat the first block of size size;
** else :
**  return NULL;
*/

void		*new_zone(void *addr, size_t size, t_zone *prev)
{
	struct rlimit	limit;
	t_zone			*zone;
	size_t			alloc;
	void			*rslt;

	printf("size:%zu\n", size);
	alloc = alloc_size(size);
	printf("alloc size:%zu\n", alloc);
	getrlimit(RLIMIT_MEMLOCK, &limit);
	if (alloc > limit.rlim_cur)
	{
		alloc = size + sizeof(t_block) + sizeof(t_zone);
		if (alloc > limit.rlim_cur)
		{
			write(2, "not enought space\n", 18);
			return ((void*)0);
		}
	}
	if ((rslt = mmap(addr, alloc, PROT_READ | PROT_WRITE, MAP_ANON
					| MAP_PRIVATE, -1, 0)) == MAP_FAILED)
	{
		write(2, "mmap failed\n", 12);
		return ((void*)0);
	}
	printf("NEW ALLLOC FROM %p TO %p\n", rslt, rslt + alloc);
	printf("new zone at %p\n", rslt);
	zone = rslt;
	zone->size = alloc - sizeof(t_zone);
	if (prev)
		prev->next = zone;
	zone->next = (void*)0;
	zone->use_space = 0;
	return (new_block(rslt + sizeof(t_zone), size, (t_zone*)rslt, (void*)0));
}
