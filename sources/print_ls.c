/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/02/04 16:13:27 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		g_first = 1;

void	print_ls(uint16_t opt, t_file *file, t_wid *wid, int dir)
{
	if (file && opt & L_LOW && dir)
		ft_printf("total %d\n", file->total);
	if (opt & R_LOW)
		revorder(opt, file, wid);
	else
		inorder(opt, file, wid);
}

void	revorder(uint16_t opt, t_file *file, t_wid *wid)
{
	if (file != NULL)
	{
		revorder(opt, file->right, wid);
		if (opt & L_LOW)
			long_format(opt, file, wid);
		else
			print_name(opt, file);
		g_first = 0;
		revorder(opt, file->left, wid);
	}
}

void	inorder(uint16_t opt, t_file *file, t_wid *wid)
{
	if (file != NULL)
	{
		inorder(opt, file->left, wid);
		if (opt & L_LOW)
			long_format(opt, file, wid);
		else
			print_name(opt, file);
		g_first = 0;
		inorder(opt, file->right, wid);
	}
}

void	print_name(uint16_t opt, t_file *file)
{
	if (S_ISLNK(file->info.st_mode) && opt & L_LOW)
		return (print_link(opt, file));
	if (opt & G_UPP)
		set_color(file->info);
	if (!g_first && !(opt & ONE) && !(opt & L_LOW))
		ft_printf("\t");
	ft_printf("%s", file->name);
	if (opt & G_UPP)
		write(1, "\x1b[0m", 5);
	if (opt & F_UPP)
		print_type(file->info);
	if (opt & ONE || opt & L_LOW)
		ft_printf("\n");
}
