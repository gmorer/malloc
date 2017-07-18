/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/13 15:25:45 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * change the size if enought place after ptr, return ptr
 *
 * or new malloc then memcpy then free ptr
 *
 * if ptr == NULL -> malloc
 *
 * if size == 0 ->
 */

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

#ifdef FINAL
void	*realloc(void *ptr, size_t len)		// a uncomment pour le rendu final
#endif
#ifndef FINAL
void	*ft_realloc(void *ptr, size_t len)	// a supprimer pour le rendu final
#endif
{
	t_block		*block;
	void		*new;

	if (len == 0)
	{
#ifdef FINAL
		free(ptr);
#endif
#ifndef FINAL
		ft_free(ptr);
#endif
		return ((void*)0);
	}
	if (ptr == (void*)0)
#ifdef FINAL
		return (malloc(len));
#endif
#ifndef FINAL
		return (ft_malloc(len));
#endif
	if ((valid_addr(ptr)) == (void*)0)
	{
		printf("realloc bad ptr\n");
		return (NULL);
	}
	block = (t_block*)ptr - 1;
	if (len == block->size)
		return (ptr);
	if (len > block->size)
	{
		if (enought_space_after(block, len) != 0)
			return (fusion(block, len));
		else
		{
			free(ptr);
			new = malloc(len);
		}
	}
	return (malloc(len));
}
