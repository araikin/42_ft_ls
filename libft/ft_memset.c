/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 22:13:13 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/19 22:46:46 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*copy;
	unsigned char	n;

	n = (unsigned char)c;
	copy = (unsigned char *)b;
	while (len--)
		*copy++ = n;
	return (b);
}
