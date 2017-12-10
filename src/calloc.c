/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 14:16:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/12/10 14:21:04 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void		ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*x;

	i = 0;
	x = s;
	while (i < n)
	{
		x[i] = (char)0;
		i++;
	}
}

void	*calloc(size_t count, size_t size)
{
	void	*rslt;

	if (!count || !size)
		return (NULL);
	rslt = malloc(count * size);
	ft_bzero(rslt, count * size);
	return (rslt);
}
