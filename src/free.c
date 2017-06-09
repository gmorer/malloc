/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:04 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/09 21:07:58 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//void	free(void *ptr)		// a uncomment pour le rendu final
void	ft_free(void *ptr)	// a supprimer pour le rendu final
{
	t_block *addr;
	t_zone	*zone;

	if ((zone = valid_addr(ptr)) == (void*)0)
		return ;
	addr = ptr;
	addr->free = 1;
	if (is_empty_zone(zone))
	{
		write(1, "the real free\n", 14);
		munmap(zone - sizeof(t_zone), zone->size + sizeof(t_zone));
	}
	return ;
}
