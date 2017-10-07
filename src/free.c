/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:04 by gmorer            #+#    #+#             */
/*   Updated: 2017/10/07 06:17:59 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

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

void	ft_free(void *ptr)		// a uncomment pour le rendu final
{
	t_block *addr;
	t_zone	*zone;

	printf("free of:%p\n", ptr);
	if ((zone = valid_addr(ptr)) == (void*)0)
	{
		printf("free bad ptr\n");
		return ;
	}
	printf("%p is valid and in the zone %p\n", ptr, zone);
	addr = ptr - sizeof(t_block);
	addr->free = 1;
	if (is_empty_zone(zone) && zone->next == (void*)0)
	{
		write(1, "the real free\n", 14);
		printf("free : %p size = %lu\n", zone, zone->size + sizeof(t_zone));
		munmap(zone, zone->size + sizeof(t_zone));
		return ;
	}
	defragment(addr);
	return ;
}
