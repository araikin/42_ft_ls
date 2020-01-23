/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:32:40 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:34:22 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_specifiers	*g_dispatch[] = {
	handle_c,
	handle_s,
	handle_p,
	handle_di,
	handle_di,
	handle_di,
	handle_ouxx,
	handle_ouxx,
	handle_ouxx,
	handle_ouxx,
	handle_f,
	handle_percent
};

int		parse_format(va_list *argp, char *format, int *len)
{
	t_format	*data;
	char		*result;
	int			n;

	result = NULL;
	if (!(data = initialize_format()))
		return (0);
	*len += 1;
	set_params(argp, data, format, len);
	if (data->spec == '\0')
		return (clear_format(data));
	n = apply_params(argp, data);
	free(data);
	return (n);
}

void	set_params(va_list *argp, t_format *data, char *format, int *len)
{
	char	*params;
	int		pos;

	pos = 0;
	params = get_all_params(format, *len);
	set_flags(params, data, &pos);
	set_width(argp, params, data, &pos);
	set_precision(params, data, &pos);
	set_length(params, data, &pos);
	set_specifier(params, data, &pos);
	*len += pos;
	ft_strdel(&params);
}

char	*get_all_params(char *format, int i)
{
	char	*params;
	int		pos;

	pos = 0;
	while (format[i + pos] && !is_specifier(format[i + pos]))
		pos++;
	params = ft_strnew(pos + 1);
	pos = 0;
	while (format[i + pos])
	{
		if (!is_specifier(format[i + pos]))
			params[pos] = format[i + pos];
		else
		{
			params[pos] = format[i + pos];
			break ;
		}
		pos++;
	}
	return (params);
}

int		apply_params(va_list *argp, t_format *data)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!data)
		return (0);
	while (i < 12)
	{
		if (SPECS[i] == data->spec)
			len = g_dispatch[i](argp, data);
		i++;
	}
	return (len);
}
