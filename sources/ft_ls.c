/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:33:36 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/15 16:38:29 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	init_flags(t_flags *f)
{
	f->a_lower = 0;
	f->l_lower = 0;
	f->t_lower = 0;
	f->r_lower = 0;
	f->r_upper = 0;
}

void	ft_ls(t_flags *flags, char *name)
{
	DIR				*dir;
	struct dirent	*dp;

	if ((dir = opendir(".")) == NULL)
	{
		perror("Cannot open .");
		exit(1);
	}
	while ((dp = readdir(dir)) != NULL)
		ft_printf("%s\t%u\n", (*dp).d_name, (unsigned int)(*dp).d_type);
}

int		set_flags(t_flags *flags, char *s)
{
	int	i;

	i = 0;
	while (s[++i])
	{
		if (!is_lsflag(s[i]))
			return (i)
	}

}

int		main(int ac, char **av)
{
	t_flags	flags;
	int		i;

	i = 1;
	ft_bzero(&flags, sizeof(t_flags));
	if (ac > 1)
		if (av[1][0] == '-')
			i += set_flags(&flags, av[1]);
	if (av[i] == NULL)
		ft_ls(&flags, ft_strdup("."));
	/*
	else
		ft_ls_param(&flags, av + i);
		*/
	return (0);
}
