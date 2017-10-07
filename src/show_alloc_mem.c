/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:28:30 by gmorer            #+#    #+#             */
/*   Updated: 2017/10/07 13:41:55 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

t_zone		*g_base;

static void	print(t_block *block_tmp, unsigned int *total)
{
	printf("%p - %p : %zu octets\n", (void*)((t_block*)block_tmp + 1),
			(void*)((t_block*)block_tmp + 1) + block_tmp->size,
			(void*)((t_block*)block_tmp + 1) + block_tmp->size -
			(void*)((t_block*)block_tmp + 1));
	*total += (void*)((t_block*)block_tmp + 1) + block_tmp->size -
		(void*)((t_block*)block_tmp + 1);
	return ;
}

void		show_alloc_mem(void)
{
	t_zone			*zone_tmp;
	t_block			*block_tmp;
	unsigned int	total;

	zone_tmp = g_base;
	total = 0;
	while (zone_tmp)
	{
		if (zone_tmp->size == TINY - sizeof(t_zone))
			printf("TINY : %p\n", (void*)((t_zone*)zone_tmp + 1));
		else if (zone_tmp->size == SMALL - sizeof(t_zone))
			printf("SMALL : %p\n", (void*)((t_zone*)zone_tmp + 1));
		else
			printf("LARGE : %p\n", (void*)((t_zone*)zone_tmp + 1));
		block_tmp = (void*)((t_zone*)zone_tmp + 1);
		while (block_tmp)
		{
			print(block_tmp, &total);
			block_tmp = block_tmp->next;
		}
		zone_tmp = zone_tmp->next;
	}
	printf("Total : %u\n", total);
	return ;
}
