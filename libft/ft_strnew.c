/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 20:29:10 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/25 22:01:23 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	n;

	n = size + 1;
	if (!(str = (char *)malloc(sizeof(char) * n)))
		return (NULL);
	return (ft_memset(str, '\0', n));
}
