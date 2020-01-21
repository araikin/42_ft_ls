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

void	print_ls(unsigned int flags, t_file *file, char *path)
{
	(void)path;
	if (flags & L_LOW)
		print_table(flags, file);
	else if (flags & R_LOW)
		revorder(file);
	else
		inorder(file);
}

void	revorder(t_file *root)
{
	if (root != NULL)	
	{
		revorder(root->right);
		ft_printf("%s\n", root->name);
		revorder(root->left);
	}
}

void	inorder(t_file *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		ft_printf("%s\n", root->name);
		inorder(root->right);
	}
}

void	print_table(unsigned int flags, t_file *file)
{
	(void)flags;
	(void)file;

	ft_printf("test\n");
}
