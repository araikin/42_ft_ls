/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:07:06 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/16 11:09:30 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	destroy_file(t_file *file)
{
	if (file != NULL)
	{
		destroy_file(file->left);
		destroy_file(file->right);
		free(file->name);
		free(file);
	}
}

void	ls_error(void)
{
	ft_printf("Error\n");
}
