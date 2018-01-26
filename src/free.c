/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:04 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/26 13:44:38 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		defragment(t_block *ptr)
{
	size_t		size;
	void		*start;
	void		*end;

	if (ptr->next && ptr->next->free == 1)
	{
		ptr->next = ptr->next->next;
		if (ptr->next)
			ptr->size += ptr->next->size + sizeof(t_block);
	}
	if (ptr->prev && ptr->prev->free == 1)
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size += ptr->size + sizeof(t_block);
	}
	return ;
}

static t_zone	*get_prev_zone(t_zone *zone)
{
	t_zone		*prev;
	t_zone		*tmp;

	tmp = get_base(GET, NULL);
	while (tmp != zone)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	return (prev);
}

void			free(void *ptr)
{
	t_block		*addr;
	t_zone		*zone;
	t_zone		*base;

	base = get_base(GET, NULL);
	if (ptr < (void*)base || (zone = valid_addr(ptr)) == NULL)
		return ;
	addr = ptr - sizeof(t_block);
	addr->free = 1;
	if (is_empty_zone(zone) && zone->next == NULL)
	{
		if (zone == base)
		{
			get_base(POST, NULL);
		}
		if (addr->size <= SMALL)
			return ;
		munmap(zone, zone->size + sizeof(t_zone));
		zone = get_prev_zone(zone);
		zone->next = NULL;
		return ;
	}
	defragment(addr);
	return ;
}
