/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/11/30 11:38:12 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		enought_space_after(t_block *ptr, size_t size)
{
	if (!ptr->next || ptr->next->free == 0)
		return (0);
	if (ptr->next->size + ptr->size + sizeof(t_block) >= size)
		return (1);
	return (0);
}

void	*fusion(t_block *block, size_t size)
{
	t_block		*new;
	t_block		*old;
	size_t		old_size;

	old = (void*)block + sizeof(block) + block->size;
	old_size = old->size;
	new = (void*)block + sizeof(t_block) + size;
	new->size = (old->size + block->size) - size;
	block->size = size;
	block->next = new;
	return ((void*)block + sizeof(t_block));
}

void	*realloc(void *ptr, size_t len)
{
	t_block		*block;
	void		*new;

	if (len == 0)
		free(ptr);
	if (len == 0)
		return ((void*)0);
	if (ptr == (void*)0)
		return (malloc(len));
	new = malloc(len);
	free(ptr);
	return (new);
}
