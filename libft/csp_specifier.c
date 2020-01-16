/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp_specifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:06:59 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:34:47 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		handle_c(va_list *argp, t_format *data)
{
	int		c;
	char	flag;

	c = va_arg(*argp, int);
	flag = (data->flags & ZERO && !(data->flags & MINUS)) ? '0' : ' ';
	if (data->width < 1)
		data->width = 1;
	data->w_rem = data->width - 1;
	if (data->flags & MINUS)
		ft_putchar(c);
	while (data->w_rem--)
		ft_putchar(flag);
	if (data->width > 0 && (!(data->flags) || !(data->flags & MINUS)))
		ft_putchar(c);
	return (data->width);
}

int		handle_s(va_list *argp, t_format *data)
{
	char	*str;
	int		len;
	char	flag;
	int		count;

	str = va_arg(*argp, char *);
	str = (str == NULL) ? "(null)" : str;
	len = (int)ft_strlen(str);
	flag = (data->flags & ZERO && !(data->flags & MINUS)) ? '0' : ' ';
	len = (data->prec == 0) ? len : (ft_min(data->prec, len));
	len = (data->prec == -1) ? 0 : len;
	data->w_rem = (data->width - len < 0) ? 0 : (data->width - len);
	count = len + data->w_rem;
	if (data->flags & MINUS)
		while (len-- && *str)
			ft_putchar(*str++);
	while (data->w_rem--)
		ft_putchar(flag);
	if (len > 0 && (!(data->flags) || !(data->flags & MINUS)))
		while (len-- && *str)
			ft_putchar(*str++);
	return (count);
}

void	adjust_p(t_format *data, char *str)
{
	(data->flags & MINUS) ? (ft_putstr("0x")) : (ft_putstr(""));
	(data->flags & MINUS) ? (print_rem(data->p_rem, '0')) : ft_putstr("");
	(data->flags & MINUS) ? (ft_putstr(str)) : ft_putstr("");
	(data->flags & MINUS) ? print_rem(data->w_rem, ' ') : ft_putstr("");
	if ((data->flags && !(data->flags & MINUS)) || !data->flags)
	{
		if (data->prec || (!data->prec && !(data->flags & ZERO)))
		{
			print_rem(data->w_rem, ' ');
			ft_putstr("0x");
			print_rem(data->p_rem, '0');
			ft_putstr(str);
		}
		else if (!data->prec && (data->flags & ZERO))
		{
			ft_putstr("0x");
			print_rem(data->w_rem, '0');
			ft_putstr(str);
		}
	}
}

int		handle_p(va_list *argp, t_format *data)
{
	void	*ptr;
	char	*str;
	int		len;

	ptr = va_arg(*argp, void *);
	str = itoa_base((unsigned long long)ptr, 16, 'l');
	if (str[0] == '0' && str[1] == '\0' && data->prec == -1)
	{
		ft_putstr("0x");
		return (2);
	}
	len = (int)ft_strlen(str);
	if (data->prec > len)
		data->p_rem = data->prec - len;
	if (len + data->p_rem + 2 <= data->width)
		data->w_rem = data->width - len - data->p_rem - 2;
	len = len + 2 + data->p_rem + data->w_rem;
	adjust_p(data, str);
	free(str);
	return (len);
}

int		handle_percent(va_list *argp, t_format *data)
{
	int		len;
	char	flag;

	(void)argp;
	flag = ' ';
	if (data->flags & ZERO && !(data->flags & MINUS))
		flag = '0';
	data->w_rem = data->width - 1;
	data->w_rem = (data->w_rem < 0) ? 0 : data->w_rem;
	len = data->w_rem + 1;
	if (data->spec == '%')
	{
		if (data->flags & MINUS)
			ft_putchar('%');
		print_rem(data->w_rem, flag);
		if (!(data->flags & MINUS))
			ft_putchar('%');
	}
	return (len);
}
