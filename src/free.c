/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:04 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/12 17:17:04 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

#ifdef FINAL
void	free(void *ptr)		// a uncomment pour le rendu final
#endif
#ifndef FINAL
void	ft_free(void *ptr)	// a supprimer pour le rendu final
#endif
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
	}
	return ;
}
