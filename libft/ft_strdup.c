/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:44:30 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/18 22:37:09 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*dup;
	char	*copy;

	len = ft_strlen(s1) + 1;
	dup = (char*)malloc(sizeof(char) * len);
	copy = dup;
	if (dup == NULL)
		return (NULL);
	while (*s1)
	{
		*dup = *s1;
		dup++;
		s1++;
	}
	*dup = '\0';
	return (copy);
}
