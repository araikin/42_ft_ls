/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 13:20:44 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:36:32 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'o' || c == 'u' ||
			c == 'x' || c == 'X' || c == 'd' || c == 'i' || c == 'f' ||
			c == 'D' || c == '%');
}

int		is_flag(char c)
{
	return (c == '-' || c == '+' || c == ' ' || c == '0' || c == '#');
}

int		is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int		is_length(char *params, int i)
{
	if (params[i] == 'l' && params[i + 1] != 'l')
		return (1);
	if (params[i] == 'l' && params[i + 1] == 'l')
		return (2);
	if (params[i] == 'h' && params[i + 1] != 'h')
		return (3);
	if (params[i] == 'h' && params[i + 1] == 'h')
		return (4);
	if (params[i] == 'L')
		return (5);
	return (-1);
}
