/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 15:40:32 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/28 17:15:25 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
			ft_printf("%s\n", file->name);
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
			ft_printf("%s\n", file->name);
		inorder(opt, file->right, wid);
	}
}

void	ls_output(int mode, char *arg)
{
	char	*tmp;
	int		i;
	int		k;

	tmp = NULL;
	k = 0;
	if (mode == 1)
	{
		ft_printf("ft_ls: illegal option -- %c\n", arg[0]);
		ft_printf("usage: ./ft_ls [-ARalrt] [file ...]\n");
		exit(EXIT_SUCCESS);
	}
	else if (mode == 2)
		ft_printf("ft_ls: %s: No such file or directory\n", arg);
	else if (mode == 3)
	{
		i = -1;
		while (arg[++i])
			if (arg[i] == '/')
				k = i + 1;
		tmp = k > 0 ? ft_strdup(&arg[k]) : ft_strdup(arg);
		ft_printf("ft_ls: %s: Permission denied\n", tmp);
		free(tmp);
	}
}
