/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:24:23 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/26 13:11:15 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(char const *s1, char c, char const *s2)
{
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (0);
	r = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (r == NULL)
		return (NULL);
	while (s1[j] != '\0')
		r[i++] = s1[j++];
	r[i++] = c;
	j = 0;
	while (s2[j] != '\0')
		r[i++] = s2[j++];
	r[i] = '\0';
	return (r);
}
