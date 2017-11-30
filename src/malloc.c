/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:40:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/11/30 11:37:45 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
** if first malloc :
**  creat new elem on g_base and return adress of 0 + sizeof t_block and t_zone;
** else :
**  look at space avaibality
**   if space avaible :
**    return (creat new block ine the non-full zone) + sizeof t_block
**   else
**    return (creat new zone after last zone) + size of t_block and t_zone;
*/

t_zone	**get_static(void)
{
	static t_zone	*base = (void*)0;

	return (&base);
}

t_zone	*get_base(void)
{
	return (*get_static());
}

void	*malloc(size_t size)
{
	void	*addr;
	t_zone	*temp;
	t_zone	*base;

	base = get_base();
	if (size == 0 || size > UINT_MAX)
		return ((void*)0);
	if (base == ((void*)0))
	{
		addr = new_zone((void*)0, size, NULL);
		base = addr == (void*)0 ? addr : addr - sizeof(t_zone) -
			sizeof(t_block);
		return (addr);
	}
	if ((addr = some_place(size)) != (void*)0)
	{
		return (addr);
	}
	temp = base;
	while (temp->next)
		temp = temp->next;
	return (new_zone((void*)temp + sizeof(t_zone) + temp->size, size, temp));
}
