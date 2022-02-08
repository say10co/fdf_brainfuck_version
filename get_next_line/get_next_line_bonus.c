/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adriouic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:34:35 by adriouic          #+#    #+#             */
/*   Updated: 2021/11/18 17:15:01 by adriouic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_strip(char **s, int rv, char *buff, int fd)
{
	int		len;
	char	*temp;
	char	*temp1;

	free(buff);
	buff = NULL;
	if (!s[fd] || rv < 0)
		return (NULL);
	len = 0;
	while (s[fd][len] != '\n' && s[fd][len])
		len++;
	temp = ft_substr(s[fd], 0, len + 1);
	temp1 = ft_substr(s[fd], len + 1, ft_strlen(s[fd]) - len);
	free(s[fd]);
	if (temp1[0] == '\0' )
	{
		s[fd] = NULL;
		free(temp1);
	}
	else
		s[fd] = temp1;
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*s[OPEN__MAX];
	char		*buffer;
	char		*temp;
	int			rv;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	rv = read(fd, buffer, BUFFER_SIZE);
	while (rv > 0)
	{
		buffer[rv] = '\0';
		if (!s[fd])
			s[fd] = ft_strdup(buffer);
		else if (buffer)
		{
			temp = ft_strjoin(s[fd], buffer);
			free(s[fd]);
			s[fd] = temp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
		rv = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_strip(s, rv, buffer, fd));
}
