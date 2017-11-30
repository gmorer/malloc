/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:29 by gmorer            #+#    #+#             */
/*   Updated: 2017/11/30 11:38:28 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t			alloc_size(size_t size)
{
	size_t		page;

	page = getpagesize();
	size += sizeof(t_block) + sizeof(t_zone);
	if (size < TINY)
		return (TINY);
	if (size < SMALL)
		return (SMALL);
	return ((size + page - 1) / page * page);
}

t_block			*find_empty_block(size_t size, t_zone *zone)
{
	t_block		*tmp;

	tmp = (void*)((t_zone*)zone + 1);
	while (tmp)
	{
		if (tmp->free && tmp->size > size + sizeof(t_block) + 1)
		{
			new_block(tmp + size + sizeof(t_block), tmp->size -
					(size + sizeof(t_block)), zone, tmp);
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

	tmp = get_base();
	size += sizeof(t_block);
	while (tmp)
	{
		if ((rslt = find_empty_block(size, tmp)) != (void*)0)
			return (rslt + 1);
		if (tmp->size - tmp->use_space >= size + sizeof(t_block))
		{
			rslt = (void*)((t_zone*)tmp + 1);
			while (rslt->next)
				rslt = rslt->next;
			rslt = new_block((void*)rslt + sizeof(t_block) + rslt->size,
					size - sizeof(t_block), tmp, rslt);
			return (rslt);
		}
		tmp = tmp->next;
	}
	return ((void*)0);
}

t_zone			*valid_addr(void *addr)
{
	t_zone	*zone_tmp;
	t_block	*block_tmp;

	zone_tmp = get_base();
	while (zone_tmp && (void*)((void*)zone_tmp + sizeof(t_zone) +
				zone_tmp->size) < addr)
		zone_tmp = zone_tmp->next;
	if (zone_tmp == (void*)0)
		return ((void*)0);
	block_tmp = (void*)((t_zone*)zone_tmp + 1);
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

	tmp = (void*)((t_zone*)addr + 1);
	while (tmp)
	{
		if (tmp->free == 0)
		{
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
