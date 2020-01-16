/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 19:54:23 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/30 20:04:17 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *lst, void *data, int (*cmp)())
{
	t_list	*to_find;

	to_find = lst;
	while (to_find != NULL)
	{
		if ((*cmp)(to_find->content, data) == 0)
			return (to_find);
		to_find = to_find->next;
	}
	return (NULL);
}
