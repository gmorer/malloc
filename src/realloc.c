/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:41:16 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/12 17:22:30 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

#ifdef FINAL
void	*realloc(void *ptr, size_t len)		// a uncomment pour le rendu final
#endif
#ifndef FINAL
void	*ft_realloc(void *ptr, size_t len)	// a supprimer pour le rendu final
#endif
{
	write(1, "enter in realloc\n", 17);
	//ft_free(ptr);
	//return (ft_malloc(len));
	free(ptr);
	return (malloc(len));
}
