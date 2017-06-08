/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:29 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/08 17:08:32 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone		*g_base;

size_t		alloc_size(size_t size)
{
	int		page;

	page = getpagesize();
	size += sizeof(t_zone) + sizeof(t_zone);
	if (size < TINY)
		return ((TINY + page - 1) / page * page);
	if (size < SMALL)
		return ((SMALL + page - 1) / page * page);
	return ((size + page - 1) / page * page);
}

t_block		*find_empty_block(size_t size, t_zone *zone)
{
	t_block		*tmp;

	tmp = (t_block*)(zone + sizeof(t_zone));
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

void		*some_place(size_t size)
{
	t_zone		*tmp;
	t_block		*rslt;

	tmp = g_base;
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
	return ((void*)0);
}
