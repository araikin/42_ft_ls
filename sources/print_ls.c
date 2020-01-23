/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/22 17:10:55 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	print_ls(uint8_t flags, t_file *file, t_wid *wid)
{
	if (flags & R_LOW)
		revorder(flags, file, wid);
	else
		inorder(flags, file, wid);
}

void	revorder(uint8_t flags, t_file *root, t_wid *wid)
{
	if (root != NULL)
	{
		revorder(flags, root->right, wid);
		if (flags & L_LOW)
			print_l_low(root, wid);
		else
			ft_printf("%s\n", root->name);
		revorder(flags, root->left, wid);
	}
}

void	inorder(uint8_t flags, t_file *root, t_wid *wid)
{
	if (root != NULL)
	{
		inorder(flags, root->left, wid);
		if (flags & L_LOW)
			print_l_low(root, wid);
		else
			ft_printf("%s\n", root->name);
		inorder(flags, root->right, wid);
	}
}


