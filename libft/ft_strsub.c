/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 00:02:30 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/26 23:20:44 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = (int)len + 1;
	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * n)))
		return (NULL);
	while (s[start] && n > 1)
	{
		str[i] = s[start];
		i++;
		start++;
		n--;
	}
	str[i] = '\0';
	return (str);
}
