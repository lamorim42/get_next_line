/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:57:44 by lamorim           #+#    #+#             */
/*   Updated: 2021/09/21 18:02:32 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*save_buf[FD_MAX];
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FD_MAX)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		free(buf);
		return (NULL);
	}
	read_file(fd, &buf, &save_buf[fd], &line);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	return (line);
}

int	read_file(int fd, char **buf, char **save_buf, char **line)
{
	char	*temp;
	int		r;

	r = 1;
	if (!*save_buf)
		*save_buf = ft_strdup("");
	while (r && !ft_strchr(*save_buf, N))
	{
		r = read(fd, *buf, BUFFER_SIZE);
		(*buf)[r] = '\0';
		temp = *save_buf;
		*save_buf = ft_strjoin(temp, *buf);
		free (temp);
	}
	get_line(save_buf, line);
	if (!**line)
	{
		free(*line);
		*line = NULL;
	}
	return (r);
}

void	get_line(char **save_buf, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*save_buf)[i] != N && (*save_buf)[i])
		i++;
	if ((*save_buf)[i] == N)
	{
		temp = *save_buf;
		*line = ft_substr(temp, 0, i + 1);
		*save_buf = ft_strdup(temp + i + 1);
		free(temp);
	}
	else
	{
		*line = ft_strdup(*save_buf);
		free(*save_buf);
		*save_buf = NULL;
	}
}
