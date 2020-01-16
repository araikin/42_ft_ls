/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 22:32:38 by asultanb          #+#    #+#             */
/*   Updated: 2019/09/26 23:28:11 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**memory(char const *s, int words_num, int m, char c)
{
	char			**arr;
	unsigned int	i;
	unsigned int	start;

	i = 0;
	start = 0;
	arr = NULL;
	if (!(arr = (char **)malloc(sizeof(char *) * (words_num + 1))))
		return (NULL);
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		arr[m++] = ft_strsub(s, start, i - start);
		start = 0;
		while (s[i] == c)
			i++;
	}
	arr[m] = 0;
	return (arr);
}

char		**ft_strsplit(char const *s, char c)
{
	int		words_num;
	char	**arr;

	arr = NULL;
	if (s)
	{
		words_num = ft_countwords(s, c);
		arr = memory(s, words_num, 0, c);
	}
	return (arr);
}
