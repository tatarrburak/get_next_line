/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: butatar <butatar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 13:47:49 by butatar           #+#    #+#             */
/*   Updated: 2023/08/29 02:43:18 by butatar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_end_ofline(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (1);
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_read_line(int fd, char *str)
{
	char	*buffer;
	int		byt;

	buffer = malloc(sizeof(char *) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byt = 1;
	while (ft_end_ofline(str) && byt != 0)
	{
		byt = read(fd, buffer, BUFFER_SIZE);
		if (byt < 0)
		{
			free(str);
			free(buffer);
			return (0);
		}
		buffer[byt] = '\0';
		str = ft_strjoin(str, buffer);
	}
	if (!str)
		return (NULL);
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*out;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_read_line(fd, str);
	if (!str)
		return (NULL);
	out = ft_next_line(str);
	str = ft_new_line(str);
	return (out);
}
