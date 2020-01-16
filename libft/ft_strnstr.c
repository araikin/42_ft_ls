/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 21:36:01 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/26 22:46:28 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*start;
	char	*pattern;
	size_t	len_copy;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		start = (char *)haystack;
		pattern = (char *)needle;
		len_copy = len;
		while (*haystack && *pattern && *haystack == *pattern && len > 0)
		{
			haystack++;
			pattern++;
			len--;
		}
		if (!*pattern)
			return (start);
		haystack = start + 1;
		len = len_copy;
		len--;
	}
	return (NULL);
}
