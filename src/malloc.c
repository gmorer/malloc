/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:40:52 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/09 20:34:23 by gmorer           ###   ########.fr       */
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

//void	*malloc(size_t size)	// a uncomment pour le rendu final
void	*ft_malloc(size_t size)	// a supprimer pour le rendu final
{
	void	*addr;
	t_zone	*temp;

	write(1, "malloc entrance\n", 16);
	if (g_base == ((void*)0))
	{
		write(1, "first malloc\n", 13);
		addr = new_zone((void*)0, size, NULL);
		g_base = addr - sizeof(t_zone) - sizeof(t_block);
		return (addr);;
	}
	if ((addr = some_place(size)) != (void*)0)
	{
		write(1, "return some place in an existing block\n", 42);
		return (addr);
	}
	temp = g_base;
	while(temp->next)
		temp = temp->next;
	return (new_zone(temp + sizeof(t_zone) + temp->size, size, temp));
}
