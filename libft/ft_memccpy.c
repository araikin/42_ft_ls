/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:33:09 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/20 19:37:04 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	char			*d;
	const char		*s;

	d = dst;
	s = src;
	while (n--)
	{
		if ((unsigned char)*s == (unsigned char)c)
		{
			*d++ = *s;
			return (d);
		}
		*d++ = *s++;
	}
	return (NULL);
}
