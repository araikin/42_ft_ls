/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:01:32 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:35:00 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_sign_f(t_format *data, int space, int sign)
{
	if (space)
		(data->flags & PLUS) ? ft_putchar('+') : ft_putchar(' ');
	(sign == -1) ? ft_putchar('-') : ft_putstr("");
}

int		f_prec_zero(t_format *data, long long int n, int sign, int len)
{
	char	flag;
	int		space;
	int		hash;

	hash = (data->flags & HASH) ? 1 : 0;
	space = (n >= 0 && (data->flags & SPACE || data->flags & PLUS)) ? 1 : 0;
	flag = (data->flags & ZERO && !(data->flags & MINUS)) ? '0' : ' ';
	data->w_rem = data->width - len - ((n < 0) ? 1 : 0) - space - hash;
	data->w_rem = (data->w_rem < 0) ? 0 : data->w_rem;
	if (data->flags & MINUS)
	{
		print_sign_f(data, space, sign);
		putnbr_ll('f', (unsigned long long)(n * sign), 10);
		(data->flags & HASH) ? ft_putchar('.') : ft_putstr("");
	}
	(flag == '0') ? print_sign_f(data, space, sign) : ft_putstr("");
	print_rem(data->w_rem, flag);
	if (!(data->flags & MINUS))
	{
		(flag == ' ') ? print_sign_f(data, space, sign) : ft_putstr("");
		putnbr_ll('f', (unsigned long long)(n * sign), 10);
		(data->flags & HASH) ? ft_putchar('.') : ft_putstr("");
	}
	return (len + ((n < 0) ? 1 : 0) + space + data->w_rem + hash);
}

void	print_f_prec(t_format *data, long double f)
{
	long double		fraction;
	int				prec;
	long long int	n;
	long double		round;

	prec = data->prec;
	round = get_round(data->prec);
	n = (long long int)f;
	fraction = f - n + round;
	n += ((fraction > 1.0) ? 1 : 0);
	fraction -= ((fraction > 1.0) ? 1 : 0);
	putnbr_ll('f', (unsigned long long)n, 10);
	ft_putchar('.');
	while (prec--)
	{
		fraction *= 10;
		ft_putchar((int)fraction + '0');
		fraction -= (long double)((int)fraction);
	}
}

int		f_prec(t_format *data, int len, long double f, int sign)
{
	char				flag;
	int					space;
	int					i;
	int					neg;

	i = 10;
	neg = (sign == -1) ? 1 : 0;
	space = (sign == 1 && (data->flags & SPACE || data->flags & PLUS)) ? 1 : 0;
	flag = (data->flags & ZERO && !(data->flags & MINUS)) ? '0' : ' ';
	data->w_rem = data->width - data->prec - len - 1 - space - neg;
	data->w_rem = (data->w_rem < 0) ? 0 : data->w_rem;
	(data->flags & MINUS) ? print_sign_f(data, space, sign) : ft_putstr("");
	(data->flags & MINUS) ? print_f_prec(data, f * sign) : ft_putstr("");
	(flag == '0') ? print_sign_f(data, space, sign) : ft_putstr("");
	print_rem(data->w_rem, flag);
	if (!(data->flags & MINUS))
	{
		(flag == ' ') ? print_sign_f(data, space, sign) : ft_putstr("");
		print_f_prec(data, f * sign);
	}
	return (len + 1 + neg + data->w_rem + space + data->prec);
}

int		handle_f(va_list *argp, t_format *data)
{
	long double	f;
	int			sign;
	int			len;
	long double	round;

	if (data->length & UL)
		f = va_arg(*argp, long double);
	else
		f = va_arg(*argp, double);
	sign = (f < 0) ? -1 : 1;
	data->prec = (data->prec == 0) ? 6 : data->prec;
	round = (data->prec == -1) ? 0.5 : get_round(data->prec);
	if (data->prec == -1)
	{
		f += round * (long double)sign;
		len = ft_numlen((unsigned long long)((long long int)f * sign), 10);
		return (f_prec_zero(data, (long long int)f, sign, len));
	}
	len = ft_numlen((unsigned long long)(((long long int)(f +
					round * (long double)sign)) * sign), 10);
	return (f_prec(data, len, f, sign));
}
