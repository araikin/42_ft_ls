/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 22:54:20 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/30 17:59:18 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	memory(char const *s, t_list **lst, char c)
{
	t_list	*tmp;
	char	*word_str;
	size_t	i;
	size_t	start;

	i = 0;
	start = 0;
	tmp = NULL;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		word_str = ft_strsub(s, start, i - start);
		tmp = ft_lstnew(word_str, i - start);
		ft_lstpush(lst, tmp);
		start = 0;
		while (s[i] == c)
			i++;
	}
}

t_list		*ft_strsplit_list(char const *s, char c)
{
	t_list	*lst;
	t_list	*copy;

	lst = NULL;
	copy = lst;
	if (s)
		memory(s, &lst, c);
	return (lst);
}
