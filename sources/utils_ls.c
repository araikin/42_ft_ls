/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/22 17:31:43 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	set_lsflags(uint8_t *flags, char *s)
{
	int	i;

	i = 0;
	while (s[++i])
		if (!is_lsflag(flags, s[i]))
			ft_printf("illegal flag: %c\n", s[i]);
}

int		is_lsflag(uint8_t *flags, char c)
{
	if (c == 'a')
		*flags = *flags | A_LOW;
	else if (c == 'A')
		*flags = *flags | A_UPP;
	else if (c == 'l')
		*flags = *flags | L_LOW;
	else if (c == 't')
		*flags = *flags | T_LOW;
	else if (c == 'r')
		*flags = *flags | R_LOW;
	else if (c == 'R')
		*flags = *flags | R_UPP;
	else
		return (0);
	return (1);
}

void	set_wid(t_file *root, t_wid *wid)
{
	if (root != NULL)
	{
		set_wid(root->left, wid);
		if (wid->links < ft_digitcnt((int)root->info.st_nlink))
			wid->links = ft_digitcnt((int)root->info.st_nlink);
		if (wid->uid < (int)ft_strlen(getpwuid(root->info.st_uid)->pw_name))
			wid->uid = (int)ft_strlen(getpwuid(root->info.st_uid)->pw_name);
		if (wid->gid < (int)ft_strlen(getgrgid(root->info.st_gid)->gr_name))
			wid->gid = (int)ft_strlen(getgrgid(root->info.st_gid)->gr_name);
		if (wid->size < ft_digitcnt((int)root->info.st_size))
			wid->size = ft_digitcnt((int)root->info.st_size);
		set_wid(root->right, wid);
	}
}

void	iterate_args(uint8_t flags, char **args, t_wid *wid)
{
	t_file	*f;
	int		i;

	f = NULL;
	i = -1;
	while (args[++i])
	{
		if (is_dir(args[i]))
		{
			set_info(flags, &f, args[i]);
			set_wid(f, wid);
		}
	}
	destroy_file(f);
}

void	handle_dir(uint8_t flags, char **args, t_wid *wid, int check)
{
	t_file *f;
	int		i;

	i = -1;
	while (args[++i])
	{
		f = NULL;
		if (is_dir(args[i]))
		{
			set_info(flags, &f, args[i]);
			check > 0 ? ft_putchar('\n') : ft_putstr("");
			ft_printf("%s:\n", args[i]);
			print_ls(flags, f, wid, 1);
			destroy_file(f);
		}
	}
}
