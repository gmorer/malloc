/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:04 by gmorer            #+#    #+#             */
/*   Updated: 2017/10/07 13:44:09 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone		*g_base;

void	defragment(t_block *ptr)
{
	size_t		size;
	void		*start;
	void		*end;

	if (ptr->next && ptr->next->free == 1)
	{
		ptr->next = ptr->next->next;
		ptr->size += ptr->next->size + sizeof(t_block);
	}
	if (ptr->prev && ptr->prev->free == 1)
	{
		ptr->prev->next = ptr->next;
		ptr->prev->size += ptr->size + sizeof(t_block);
	}
	return ;
}

void	free(void *ptr)
{
	t_block *addr;
	t_zone	*zone;

	if ((zone = valid_addr(ptr)) == (void*)0)
		return ;
	addr = ptr - sizeof(t_block);
	addr->free = 1;
	if (is_empty_zone(zone) && zone->next == (void*)0)
	{
		if (zone == g_base)
			g_base = (void*)0;
		munmap(zone, zone->size + sizeof(t_zone));
		return ;
	}
	defragment(addr);
	return ;
}
