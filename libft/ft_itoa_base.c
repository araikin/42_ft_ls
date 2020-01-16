/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 20:15:01 by asultanb          #+#    #+#             */
/*   Updated: 2019/10/01 20:15:03 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(long long n, int base)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= base;
		i++;
	}
	return (i);
}

char		*ft_itoa_base(int n, int base)
{
	char		*nbr_str;
	char		*base_arr;
	int			len;
	long long	n_ll;

	n_ll = (long long)n;
	if (base < 2 && base > 16)
		return (0);
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		n_ll *= -1;
	base_arr = ft_strdup("0123456789ABCDEF");
	len = ft_nbrlen(n_ll, base) + (n < 0 && base == 10);
	if (!(nbr_str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (n < 0)
		nbr_str[0] = '-';
	nbr_str[len] = '\0';
	while (n_ll != 0)
	{
		nbr_str[--len] = base_arr[n_ll % base];
		n_ll /= base;
	}
	return (nbr_str);
}
