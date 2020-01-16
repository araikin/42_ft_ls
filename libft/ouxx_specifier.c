/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ouxx_specifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 16:57:02 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:35:58 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_ox(t_format *data, uint64_t n)
{
	if (data->flags & HASH && n > 0)
	{
		(data->spec == 'x') ? ft_putstr("0x") : ft_putstr("");
		(data->spec == 'X') ? ft_putstr("0X") : ft_putstr("");
	}
}

void	ouxx_minus(t_format *data, uint64_t n, int base, char flag)
{
	print_ox(data, n);
	print_rem(data->p_rem, '0');
	if (n == 0 && data->prec == -1)
		ft_putstr("");
	else
		putnbr_ll(data->spec, (unsigned long long)n, base);
	print_rem(data->w_rem, flag);
}

void	ouxx_nomin(t_format *data, uint64_t n, int base, char flag)
{
	if (data->prec == 0 && flag == '0')
	{
		print_ox(data, n);
		print_rem(data->w_rem, flag);
	}
	if (data->prec != 0 || (data->prec == 0 && flag == ' '))
	{
		print_rem(data->w_rem, flag);
		print_ox(data, n);
	}
	print_rem(data->p_rem, '0');
	if (n == 0 && data->prec == -1)
		ft_putstr("");
	else
		putnbr_ll(data->spec, (unsigned long long)n, base);
}

int		adjust_ouxx(t_format *data, uint64_t n, int len, int base)
{
	int		hash;
	int		hex;
	char	flag;

	flag = ' ';
	if (data->flags & ZERO && !(data->flags & MINUS) && !data->prec)
		flag = '0';
	hash = (data->flags & HASH && n != 0 && data->prec <= len + 1 &&
			data->spec == 'o') ? 1 : 0;
	hex = (data->flags & HASH && n != 0 &&
			(data->spec == 'x' || data->spec == 'X')) ? 1 : 0;
	if (data->flags & HASH && n == 0 && data->prec == -1 && data->spec == 'o')
		hash = 1;
	data->p_rem = hash + ((data->prec > len) ? data->prec - len : 0);
	data->w_rem = data->width - len - data->p_rem - (hex * 2);
	data->w_rem = (data->w_rem < 0) ? 0 : data->w_rem;
	len = len + data->p_rem + data->w_rem + (hex * 2);
	if (data->flags & MINUS)
		ouxx_minus(data, n, base, flag);
	else
		ouxx_nomin(data, n, base, flag);
	return (len);
}

int		handle_ouxx(va_list *argp, t_format *data)
{
	uint64_t	n;
	int			len;
	int			base;

	if (data->spec == 'o')
		base = 8;
	else if (data->spec == 'x' || data->spec == 'X')
		base = 16;
	else
		base = 10;
	if (data->length & L)
		n = va_arg(*argp, unsigned long int);
	else if (data->length & LL)
		n = va_arg(*argp, unsigned long long int);
	else if (data->length & H)
		n = (unsigned short int)va_arg(*argp, int);
	else if (data->length & HH)
		n = (unsigned char)va_arg(*argp, int);
	else
		n = va_arg(*argp, unsigned int);
	if (n == 0 && data->prec == -1)
		len = 0;
	else
		len = ft_numlen((unsigned long long)n, base);
	return (adjust_ouxx(data, n, len, base));
}
