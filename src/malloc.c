/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:40:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/12/09 08:43:27 by gmorer           ###   ########.fr       */
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

t_zone	*get_base(enum base req, void *addr)
{
	static t_zone	*base = NULL;

	if (req == GET)
		return (base);
	else if (req == POST)
	{
		base = addr;
		return (base);
	}
	return (base);
}

void	*malloc(size_t size)
{
	void	*addr;
	t_zone	*temp;
	t_zone	*base;

	base = get_base(GET, NULL);
	if (size == 0 || size > UINT_MAX)
	{
		return (NULL);
	}
	if (base == (NULL))
	{
		addr = new_zone(NULL, size, NULL);
		get_base(POST, addr == NULL ? addr :
				addr - sizeof(t_zone) - sizeof(t_block));
		return (addr);
	}
	if ((addr = some_place(size)) != NULL)
	{
		return (addr);
	}
	temp = base;
	while (temp->next)
		temp = temp->next;
	return (new_zone((void*)temp + sizeof(t_zone) + temp->size, size, temp));
}
