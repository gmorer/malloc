/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:40:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/08 17:10:58 by gmorer           ###   ########.fr       */
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
	void	*rslt;
	void	*addr;

	if (g_base == ((void*)0))
	{
		g_base = (void*)8;
		return (new_zone((void*)0, size, NULL));
	}
	if ((addr = some_place(size)) != (void*)0)
	{
		return (add_block(addr, size));
	}
	/*
	 * need the new zone 
	 */
	return (rslt);
}
