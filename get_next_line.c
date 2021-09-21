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

#include "get_next_line.h"

int		read_file(int fd, char **buf, char **save_buf, char **line);
char	*get_line(char **save_buf, char **line);

char	*get_next_line(int fd)
{
	static char	*save_buf = NULL;
	char		*buf;
	char		*line;
	int			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		free(buf);
		return (NULL);
	}
	r = read_file(fd, &buf, &save_buf, &line);
	if (r <= 0 && !*save_buf) // aqui pode ter BO
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	free(buf);
	return (line);
}

int	read_file(int fd, char **buf, char **save_buf, char **line)
{
	char	*temp;
	int		r;

	r = 1;
	if (!*save_buf)
		*save_buf = ft_strdup("");
	while (r && !ft_strchr(*buf, N))
	{
		r = read(fd, *buf, BUFFER_SIZE);
		temp = *save_buf;
		*save_buf = ft_strjoin(temp, *buf);
		free (temp);
	}
	get_line(save_buf, line);
	return (r);
}

char	*get_line(char **save_buf, char **line)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*save_buf)[i] != N && (*save_buf)[i] != '\0')
		i++;
	if ((*save_buf)[i] == N)
	{
		*line = ft_substr(*save_buf, 0, i + 1);
		temp = *save_buf;
		*save_buf = ft_strdup(temp + i + 1);
		free(temp);
	}
	else
	{
		*line = ft_strdup(*save_buf);
		free(*save_buf);
		*save_buf = NULL;
	}
	return (*line);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*obj;
	size_t	i;

	if (nmemb * size > 2141483647)
		return (NULL);
	obj = malloc(size * nmemb);
	if (!obj)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		((char *)obj)[i] = '\0';
		i++;
	}
	return (obj);
}
