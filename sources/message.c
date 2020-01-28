/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:06:27 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/27 16:54:00 by asultanb         ###   ########.fr       */
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

void	ls_usage(void)
{
	ft_printf("usage: ./ft_ls [-ARalrt] [file ...]\n");
	exit(EXIT_SUCCESS);
}

void	ls_nooption(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n", c);
	ls_usage();	
}

void	ls_nofile(char *arg)
{
	ft_printf("ft_ls: %s: No such file or directory\n", arg);
	free(arg);
	exit(EXIT_SUCCESS);
}

void	ls_nopermission(t_file *file, char *arg)
{
	ft_printf("%s:\nft_ls: %s: Permission denied\n", arg, arg);
	destroy_file(file);
	free(arg);
	exit(EXIT_SUCCESS);
}
