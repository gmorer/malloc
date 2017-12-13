/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/12/09 08:43:43 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*y;
	char	*z;

	i = 0;
	y = (char*)dst;
	z = (char*)src;
	if (n == 0)
		return (y);
	while (i <= n)
	{
		y[i] = z[i];
		i++;
	}
	return (y);
}

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
		return (NULL);
	if (ptr == (NULL))
		return (malloc(len));
	if (ptr < (void*)get_base(GET, NULL) || valid_addr(ptr) == NULL)
		return (NULL);
	new = malloc(len);
	block = ptr - sizeof(t_block);
	ft_memcpy(new, ptr, len > block->size ? block->size : len);
	free(ptr);
	return (new);
}
