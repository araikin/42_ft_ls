/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 21:50:33 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/26 23:12:36 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*str;

	str = NULL;
	if (s)
	{
		i = -1;
		if (!(str = ft_strnew(ft_strlen(s))))
			return (NULL);
		while (s[++i])
			str[i] = f(s[i]);
		str[i] = '\0';
	}
	return (str);
}
