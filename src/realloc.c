/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:16 by gmorer            #+#    #+#             */
/*   Updated: 2018/01/05 09:22:11 by gmorer           ###   ########.fr       */
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

void		*realloc(void *ptr, size_t len)
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
