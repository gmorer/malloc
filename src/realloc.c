/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/09 19:37:13 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//void	*realloc(void *ptr, size_t len)		// a uncomment pour le rendu final
void	*ft_realloc(void *ptr, size_t len)	// a supprimer pour le rendu final
{
	write(1, "enter in realloc\n", 17);
	ft_free(ptr);
	return (ft_malloc(len));
}
