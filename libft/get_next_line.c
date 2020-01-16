/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 20:56:01 by asultanb          #+#    #+#             */
/*   Updated: 2019/11/03 15:45:36 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_line(char **arr, const int fd, char **line)
{
	char	*tmp;
	int		len;

	len = 0;
	while (arr[fd][len] != '\0' && arr[fd][len] != '\n')
		len++;
	if (arr[fd][len] == '\n')
	{
		*line = ft_strsub(arr[fd], 0, len);
		tmp = ft_strdup(&arr[fd][len + 1]);
		free(arr[fd]);
		arr[fd] = tmp;
		if (arr[fd][0] == '\0')
			ft_strdel(&arr[fd]);
	}
	else
	{
		*line = ft_strdup(arr[fd]);
		ft_strdel(&arr[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*arr[4096];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			rd;

	if (!line || fd < 0)
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if (arr[fd] == NULL)
			arr[fd] = ft_strnew(1);
		tmp = ft_strjoin(arr[fd], buff);
		free(arr[fd]);
		arr[fd] = tmp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (rd < 0)
		return (-1);
	else if (rd == 0 && (arr[fd] == NULL || arr[fd][0] == '\0'))
		return (0);
	return (get_line(arr, fd, line));
}
