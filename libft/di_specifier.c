/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:07:22 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:34:08 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_sign(t_format *data, int64_t n, int m, char flag)
{
	if (data->flags & SPACE && n >= 0 && !(data->flags & PLUS))
		ft_putchar(' ');
	(data->flags & PLUS && n >= 0) ? ft_putchar('+') : ft_putstr("");
	(n < 0 && (m == 1 || flag == ' ')) ? ft_putchar('-') : ft_putstr("");
}

void	di_minus(t_format *data, int64_t n)
{
	int		m;
	int		sign;
	char	flag;

	flag = ' ';
	m = 0;
	if (data->flags & ZERO && !(data->flags & MINUS) && !data->prec)
		flag = '0';
	sign = (n < 0) ? -1 : 1;
	if ((n < 0 && data->prec == 0) || (n >= 0 && data->flags & PLUS))
		m = 1;
	print_sign(data, n, m, flag);
	print_rem(data->p_rem, '0');
	(n == 0 && data->prec == -1) ? ft_putstr("") :
		putnbr_ll(data->spec, (unsigned long long)(n * sign), 10);
	print_rem(data->w_rem, flag);
}

void	di_nominus(t_format *data, int64_t n)
{
	int		m;
	int		sign;
	char	flag;

	flag = ' ';
	if (data->flags & ZERO && !(data->flags & MINUS) && !data->prec)
		flag = '0';
	sign = (n < 0) ? -1 : 1;
	m = ((n < 0 && data->prec == 0) || (n >= 0 && data->flags & PLUS)) ? 1 : 0;
	if (data->prec == 0 && flag == '0')
	{
		print_sign(data, n, m, flag);
		print_rem(data->w_rem, flag);
	}
	else if (data->prec != 0 || (data->prec == 0 && flag == ' '))
	{
		print_rem(data->w_rem, flag);
		print_sign(data, n, m, flag);
		print_rem(data->p_rem, '0');
	}
	(n == 0 && data->prec == -1) ? ft_putstr("") :
		putnbr_ll(data->spec, (unsigned long long)(n * sign), 10);
}

int		adjust_di(t_format *data, int64_t n, int len)
{
	int		space;
	int		is_neg;

	is_neg = (n < 0) ? 1 : 0;
	space = (n >= 0 && (data->flags & SPACE || data->flags & PLUS)) ? 1 : 0;
	data->p_rem = (data->prec > len) ? data->prec - len : 0;
	if (data->width > ft_max(data->prec, len))
		data->w_rem = data->width - len - data->p_rem - is_neg - space;
	len = len + data->p_rem + data->w_rem + space + is_neg;
	if (data->flags & MINUS)
		di_minus(data, n);
	else
		di_nominus(data, n);
	return (len);
}

int		handle_di(va_list *argp, t_format *data)
{
	int64_t n;
	int		len;
	int		sign;

	if (data->spec == 'D')
		n = va_arg(*argp, long int);
	else if (data->length & L)
		n = va_arg(*argp, long int);
	else if (data->length & LL)
		n = va_arg(*argp, long long int);
	else if (data->length & H)
		n = (short int)va_arg(*argp, int);
	else if (data->length & HH)
		n = (signed char)va_arg(*argp, int);
	else
		n = va_arg(*argp, int);
	sign = (n < 0) ? -1 : 1;
	if (n == 0 && data->prec == -1)
		len = 0;
	else
		len = ft_numlen((unsigned long long)(n * sign), 10);
	return (adjust_di(data, n, len));
}
