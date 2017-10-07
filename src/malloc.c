/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:40:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/10/07 13:44:18 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone		*g_base = ((void*)0);

/*
** if first malloc :
**  creat new elem on g_base and return adress of 0 + sizeof t_block and t_zone;
** else :
**  look at space avaibality
**   if space avaible :
**    return (creat new block ine the non-full zone) + sizeof t_block
**   else
**    retunr (creat new zone after last zone) + size of t_block and t_zone;
*/

void	*malloc(size_t size)
{
	void	*addr;
	t_zone	*temp;

	if (size == 0 || size > UINT_MAX)
		return ((void*)0);
	if (g_base == ((void*)0))
	{
		addr = new_zone((void*)0, size, NULL);
		g_base = addr - sizeof(t_zone) - sizeof(t_block);
		return (addr);
	}
	if ((addr = some_place(size)) != (void*)0)
		return (addr);
	temp = g_base;
	while (temp->next)
		temp = temp->next;
	return (new_zone((void*)temp + sizeof(t_zone) + temp->size, size, temp));
}
