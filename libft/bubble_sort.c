/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:48:19 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/10 13:49:30 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	bubble_sort(int *arr, int size)
{
	int		tmp;
	int		i;
	int		swap;

	swap = 1;
	while (swap)
	{
		swap = 0;
		i = size - 1;
		while (i >= 1)
		{
			if (arr[i] < arr[i - 1])
			{
				tmp = arr[i];
				arr[i] = arr[i - 1];
				arr[i - 1] = tmp;
				swap = 1;
			}
			i--;
		}
	}
}
