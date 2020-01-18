/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/17 15:40:33 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_table(unsigned int flags, t_file *file)
{
	ft_printf("")
}

void	print_ls(unsigned int flags, t_file *file)
{
	if (flags & L_LOW)
		print_table(flags, file);
	else if (flags & R_LOW)
		revorder(file);
	else
		inorder(file);
}
