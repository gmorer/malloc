/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:58:35 by gmorer            #+#    #+#             */
/*   Updated: 2017/06/13 10:16:52 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY 1024
# define SMALL 4096

# include <sys/mman.h>
# include <unistd.h>
# include <sys/resource.h>

typedef struct s_zone	t_zone;

typedef struct	s_block
{
	size_t			size;
	int				free;
	t_zone			*zone;
	struct s_block	*next;
	struct s_block	*prev;
}				t_block;

void			*new_block(void *addr, size_t size, t_zone *zone, t_block *prev);

struct			s_zone
{
	size_t			size;
	size_t			use_space;
	struct s_zone		*next;
};

void			*new_zone(void *addr, size_t size, t_zone *prev);

extern t_zone	*g_base;

t_zone			*valid_addr(void *ptr);
int				is_empty_zone(t_zone *zone);
void			*add_block(t_zone *zone, size_t size);
void			*some_place(size_t size);
size_t			alloc_size(size_t size);
void			free(void *ptr);					// a uncomment pour le rendu final
void			*realloc(void *ptr, size_t size);	// a uncomment pour le rendu final
void			*malloc(size_t size);				// a uncomment pour le rendu final
void			show_alloc_mem();

#endif
