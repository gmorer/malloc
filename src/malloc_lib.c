/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:29 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/09 20:58:49 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_zone		*g_base;

size_t			alloc_size(size_t size)
{
	int		page;

	page = getpagesize();
	size += sizeof(t_block) + sizeof(t_zone);
	if (size < TINY)
		return ((TINY + page - 1) / page * page);
	if (size < SMALL)
		return ((SMALL + page - 1) / page * page);
	return ((size + page - 1) / page * page);
}

t_block			*find_empty_block(size_t size, t_zone *zone)
{
	t_block		*tmp;

	tmp = (t_block*)(zone + sizeof(t_zone));
	printf("looking at %p\n", tmp);
	while (tmp)
	{
		if (tmp->free && tmp->size > size + sizeof(t_block) + 1)
		{
			new_block(tmp + size + sizeof(t_block), tmp->size - (size + sizeof(t_block)),zone,  tmp);
			tmp->size = size;
			tmp->free = 0;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return ((void*)0);
}

void			*some_place(size_t size)
{
	t_zone		*tmp;
	t_block		*rslt;

	tmp = g_base;
	printf("g_base = %p\n", g_base);
	size += sizeof(t_block);
	while (tmp)
	{
		if ((rslt = find_empty_block(size, tmp)) != (void*)0)
			return (rslt + sizeof(t_block));
		if (tmp->size >= size)
		{
			rslt = (t_block*)(tmp + sizeof(t_zone));
			while (rslt->next)
				rslt = rslt->next;
			rslt = new_block(rslt + sizeof(t_block) + rslt->size, size, tmp, rslt);
			return (rslt);
		}
		tmp = tmp->next;
	}
	write(1, "some place reuturn NULL\n", 24);
	return ((void*)0);
}

t_zone			*valid_addr(void *addr)
{
	t_zone	*zone_tmp;
	t_block	*block_tmp;

	zone_tmp = g_base;
	while (zone_tmp && (void*)(zone_tmp + sizeof(t_zone) + zone_tmp->size) < addr)
		zone_tmp = zone_tmp->next;
	if (zone_tmp == (void*)0)
		return ((void*)0);
	block_tmp = (t_block*)(zone_tmp) + sizeof(t_zone);
	while (block_tmp)
	{
		if (block_tmp == addr)
			return (zone_tmp);
		block_tmp = block_tmp->next;
	}
	return ((void*)0);
}

int				is_empty_zone(t_zone *addr)
{
	t_block		*tmp;

	tmp = (t_block*)addr + sizeof(addr);
	while (tmp)
	{
		if (tmp->free == 0)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
