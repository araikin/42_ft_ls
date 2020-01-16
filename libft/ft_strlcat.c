/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:58:59 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/29 21:55:36 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;

	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (dstsize < dlen)
		slen += dstsize;
	else
		slen += dlen;
	while (*src && dstsize > dlen + 1)
	{
		*(dst + dlen) = *src;
		dlen++;
		src++;
	}
	*(dst + dlen) = '\0';
	return (slen);
}
