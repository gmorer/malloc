/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmorer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 15:58:35 by gmorer            #+#    #+#             */
/*   Updated: 2018/02/12 11:06:47 by gmorer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY_SIZE 256
# define SMALL_SIZE 4096

# include <sys/mman.h>
# include <unistd.h>
# include <limits.h>
# include <sys/resource.h>

typedef struct s_zone	t_zone;

enum	e_base {GET, POST};
enum	e_type {TINY, SMALL, LARGE};

typedef struct			s_block
{
	size_t				size;
	int					free;
	t_zone				*zone;
	struct s_block		*next;
	struct s_block		*prev;
}						t_block;

void					*new_block(void *addr, size_t size,
		t_zone *zone, t_block *prev);

struct					s_zone
{
	enum e_type			type;
	size_t				size;
	size_t				use_space;
	struct s_zone		*next;
};

void					*new_zone(void *addr, size_t size, t_zone *prev);
enum e_type				zone_type(size_t size);
t_zone					*get_base(enum e_base req, void *addr);
t_zone					*valid_addr(void *ptr);
int						is_empty_zone(t_zone *zone);
void					*add_block(t_zone *zone, size_t size);
void					*some_place(size_t size);
size_t					alloc_size(size_t size);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
void					*calloc(size_t count, size_t size);
void					*malloc(size_t size);
void					show_alloc_mem();

#endif
