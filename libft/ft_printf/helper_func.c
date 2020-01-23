/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 14:59:37 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:35:23 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char		*itoa_base(unsigned long long n, int base, char c)
{
	char	*hex;
	char	*str;
	int		i;
	int		len;

	str = NULL;
	len = ft_numlen(n, base);
	hex = (c == 'u') ? "0123456789ABCDEF" : "0123456789abcdef";
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	while (n != 0)
	{
		str[--len] = hex[n % base];
		n /= base;
	}
	return (str);
}

void		putnbr_ll(char specifier, unsigned long long n, int base)
{
	char	*hex;

	hex = (specifier == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";
	if (n >= (unsigned long long)base)
		putnbr_ll(specifier, n / base, base);
	ft_putchar(hex[n % base]);
}

void		print_rem(int rem, char c)
{
	while (rem--)
		ft_putchar(c);
}

long double	get_round(int precision)
{
	long double n;

	n = 0.5;
	while (precision--)
		n /= 10;
	return (n);
}

int			ft_numlen(unsigned long long n, int base)
{
	int	len;

	len = 0;
	len = (n == 0) ? 1 : 0;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}
