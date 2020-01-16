/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 18:00:38 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/30 18:03:42 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		ft_putstr(lst->content);
		ft_putstr(" --> ");
		lst = lst->next;
	}
	ft_putstr("NULL");
}
