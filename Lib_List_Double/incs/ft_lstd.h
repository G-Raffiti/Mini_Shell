/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbonneva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 04:34:08 by rbonneva          #+#    #+#             */
/*   Updated: 2022/11/26 04:54:58 by rbonneva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LSTD_H
# define FT_LSTD_H
# include <stdlib.h>

# ifndef T_ERROR
#  define T_ERROR

typedef enum e_error
{
	MALLOC_ERROR = -1,
	ERROR = 0,
	SUCCESS = 1,
}	t_error;

# endif

typedef struct s_lstd
{
	void			*content;
	struct s_lstd	*next;
	struct s_lstd	*previous;
}	t_lstd;

t_lstd	*ft_lstd_at(t_lstd *lst, unsigned int nbr);
void	ft_lstd_clear(t_lstd **lst, void (*free_fct)(void *));
int		ft_lstd_contain(t_lstd *lst, void *content);
void	ft_lstd_del(t_lstd *elem, void (*free_fct)(void *));
t_lstd	*ft_lstd_first(t_lstd *lst);
t_lstd	*ft_lstd_find(t_lstd *lst, void *ref, int (*cmp)());
void	ft_lstd_foreach(t_lstd *lst, void (*f)(void *));
void	ft_lstd_foreach_if(t_lstd *lst, void (*f)(void *), void *ref, \
						int (*cmp)());
t_error	ft_lstd_insert(t_lstd **lst, void *content);
void	ft_lstd_insert_elem(t_lstd **lst, t_lstd *elem);
t_lstd	*ft_lstd_last(t_lstd *lst);
void	ft_lstd_merge(t_lstd **lst1, t_lstd *lst2);
void	ft_lstd_move(t_lstd **from, t_lstd *elem, t_lstd *after_this);
t_lstd	*ft_lstd_new(void *content);
void	ft_lstd_push_back(t_lstd **lst, void *data);
void	ft_lstd_push_back_elem(t_lstd **lst, t_lstd *elem);
void	ft_lstd_push_front(t_lstd **lst, void *data);
void	ft_lstd_push_front_elem(t_lstd **lst, t_lstd *elem);
t_lstd	*ft_lstd_push_tab(int size, void **data);
t_lstd	*ft_lstd_remove(t_lstd *elem);
void	ft_lstd_remove_if(t_lstd **lst, void *ref, int (*cmp)(), \
						void (*free_fct)(void *));
void	ft_lstd_reverse(t_lstd **lst);
int		ft_lstd_size(t_lstd *lst);
void	ft_lstd_sort(t_lstd **lst, int (*cmp)());

#endif
