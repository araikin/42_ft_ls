/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:53:48 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/19 22:06:55 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char *start;
	char *pattern;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack)
	{
		start = (char *)haystack;
		pattern = (char *)needle;
		while (*haystack && *pattern && *haystack == *pattern)
		{
			haystack++;
			pattern++;
		}
		if (!*pattern)
			return (start);
		haystack = start + 1;
	}
	return (NULL);
}
