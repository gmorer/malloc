/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:28:30 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/10 17:39:20 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_hex(char c)
{
	if (c < 10)
	{
		c += 48;
		write(1, &c, 1);
	}
	else
	{
		c += 87;
		write(1, &c, 1);
	}
}

static void	print_size(size_t n)
{
	if (n < 10)
		print_hex(n);
	else if (n > 9)
	{
		print_size(n / 10);
		print_size(n % 10);
	}
}

static void	print_address(void *addr)
{
	long	n;

	n = (long)addr;
	if (n < 16)
		print_hex(n);
	else if (n > 9)
	{
		print_address((void*)(n / (long)16));
		print_address((void*)(n % (long)16));
	}
}

static int	print(t_block *block_tmp, unsigned int *total)
{
	write(1, "0x", 2);
	print_address((void*)((t_block*)block_tmp + 1));
	write(1, " - 0x", 5);
	print_address((void*)((t_block*)block_tmp + 1) + block_tmp->size);
	write(1, " : ", 3);
	print_size(block_tmp->size);
	write(1, " octets\n", 8);
	*total += (void*)((t_block*)block_tmp + 1) + block_tmp->size -
		(void*)((t_block*)block_tmp + 1);
	return (1);
}

void		show_alloc_mem(void)
{
	t_zone			*zone_tmp;
	t_block			*block_tmp;
	unsigned int	total;

	zone_tmp = get_base(GET, NULL);
	total = 0;
	while (zone_tmp)
	{
		if (zone_tmp->size >= alloc_size(SMALL - sizeof(t_block)
					- sizeof(t_zone)) - sizeof(t_zone))
			write(1, "LARGE : 0x", 11);
		else
			write(1, zone_tmp->size == alloc_size(TINY -
					sizeof(t_block) - sizeof(t_zone)) - sizeof(t_zone) ?
					"TINY : 0x" : "SMALL : 0x", 10);
		print_address((void*)((t_zone*)zone_tmp + 1));
		write(1, "\n", 1);
		block_tmp = (void*)((t_zone*)zone_tmp + 1);
		while (block_tmp && print(block_tmp, &total))
			block_tmp = block_tmp->next;
		zone_tmp = zone_tmp->next;
	}
	write(1, "Total : ", 8);
	print_size(total);
	write(1, "\n", 1);
}
