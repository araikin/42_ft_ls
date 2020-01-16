/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 00:32:06 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/26 23:29:54 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_delim(char c)
{
	return (c == ' ' || c == '\t' | c == '\n');
}

char		*ft_strtrim(char const *s)
{
	int		start;
	int		end;

	start = 0;
	if (s)
	{
		while (is_delim(s[start]))
			start++;
		if (s[start] == '\0')
			return (ft_strnew(1));
		end = ft_strlen(s) - 1;
		while (is_delim(s[end]))
			end--;
		return (ft_strsub(s, start, (end - start + 1)));
	}
	return (NULL);
}
