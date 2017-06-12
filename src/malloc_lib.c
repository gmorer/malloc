/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:29 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/12 17:53:02 by gmorer           ###   ########.fr       */
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

	printf("zone = %p\n", zone);
	tmp = (void*)((t_zone*)zone + 1);
	printf("looking at %p\n", tmp);
	while (tmp)
	{
		if (tmp->free && tmp->size > size + sizeof(t_block) + 1) // some segf on this line
		{
			new_block(tmp + size + sizeof(t_block), tmp->size - (size + sizeof(t_block)),zone,  tmp);
			tmp->size = size;
			tmp->free = 0;
			printf("find_empty_block return %p\n", tmp);
			return (tmp);
		}
		tmp = tmp->next;
	}
	printf("no empty block in zone:%p\n", zone);
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
			//return ((void*)rslt + sizeof(t_block));
			return (rslt + 1);
		if (tmp->size - tmp->use_space >= size + sizeof(t_block))
		{
			printf("there is place in zone:%p, place_left = %lu\n", tmp, tmp->size - tmp->use_space);
			rslt = (void*)((t_zone*)tmp + 1);
			printf("1rst block for zone(%p) is block(%p) sizof = %lu\n", tmp, rslt, sizeof(t_zone));
			while (rslt->next)
				rslt = rslt->next;
			rslt = new_block((void*)rslt + sizeof(t_block) + rslt->size, size, tmp, rslt);
			return (rslt);
		}
		tmp = tmp->next;
	}
	write(1, "some place return NULL\n", 23);
	return ((void*)0);
}

t_zone			*valid_addr(void *addr)
{
	t_zone	*zone_tmp;
	t_block	*block_tmp;

	zone_tmp = g_base;
	while (zone_tmp && (void*)((void*)zone_tmp + sizeof(t_zone) + zone_tmp->size) < addr)
		zone_tmp = zone_tmp->next;
	if (zone_tmp == (void*)0)
	{
		printf("return 1\n");
		return ((void*)0);
	}
	printf("free test for valid zone : %p\n", zone_tmp);
	block_tmp = (void*)((t_zone*)zone_tmp + 1);
	printf("1rst block  = %p\n", block_tmp);
	while (block_tmp)
	{
		if (block_tmp + 1 == addr)
			return (zone_tmp);
		block_tmp = block_tmp->next;
	}
	return ((void*)0);
}

int				is_empty_zone(t_zone *addr)
{
	t_block		*tmp;

	printf("zone = %p\n", addr);
	tmp = (void*)((t_zone*)addr + 1);
	printf("zone = %p\n", addr);
	printf("test of empty_zone %p\n", tmp);
	while (tmp)
	{
		if (tmp->free == 0)
		{
			printf("%p isnt free\n", tmp);
			return (0);
		}
		printf("%p is free\n", tmp);
		tmp = tmp->next;
	}
	return (1);
}
