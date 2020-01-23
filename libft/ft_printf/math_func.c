/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:09:14 by asultanb          #+#    #+#             */
/*   Updated: 2019/12/11 15:35:46 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int		ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int		ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int		ft_abs(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}
