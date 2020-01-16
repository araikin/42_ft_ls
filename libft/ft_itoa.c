/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 22:52:04 by asultanb          #+#    #+#             */
/*   Updated: 2019/10/01 20:14:13 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long n)
{
	int len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*arr;
	int		len;
	long	nb;

	nb = (long)n;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		nb *= -1;
	len = ft_nbrlen(nb) + (n < 0);
	if (!(arr = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n < 0)
		arr[0] = '-';
	arr[len] = '\0';
	while (nb > 0)
	{
		arr[--len] = nb % 10 + '0';
		nb /= 10;
	}
	return (arr);
}
