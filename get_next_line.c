/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:57:44 by lamorim           #+#    #+#             */
/*   Updated: 2021/09/14 16:51:11 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save_buf = NULL;
	char		*line;
	int			r;

	buf = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	r = read(fd, buf, BUFFER_SIZE);
	if (r < 0 && !save_buf)
		return (NULL);
	line = NULL;
	if (r == 0)
	{
		line = ft_substr(save_buf, 0, ft_len_to_n(save_buf));
		free(save_buf);
		save_buf = NULL;
		free(buf);
		buf = NULL;
		return (line);
	}
	line = read_file(fd, r, &buf, &save_buf);
	return (line);
}

char	*get_one_line(const char *buf, char **save_buf, char *line)
{
	size_t	len;
	char	*temp;

	len = ft_len_to_n(buf);
	if (!*save_buf)
	{
		*save_buf = ft_substr(buf, len, BUFFER_SIZE - len);
		line = ft_substr(buf, 0, len);
	}
	else
	{
		temp = *save_buf;
		*save_buf = ft_strjoin(*save_buf, buf);
		free(temp);
		len = ft_len_to_n(*save_buf);
		line = ft_substr(*save_buf, 0, len);
		temp = *save_buf;
		*save_buf = ft_strjoin(*save_buf + len, "");
		free(temp);
	}
	return (line);
}

char	*read_file(int fd, int r, char **buf, char **save_buf)
{
	char	*temp;
	char	*line;

	line = NULL;
	while (r > 0)
	{
		if (buf && ft_strchr(*buf, '\n'))
		{
			line = get_one_line(*buf, save_buf, line);
			free(*buf);
			buf = NULL;
			break ;
		}
		else
		{
			if (!*save_buf)
				*save_buf = ft_substr(*buf, 0, BUFFER_SIZE);
			else
			{
				temp = *save_buf;
				*save_buf = ft_strjoin(*save_buf, *buf);
				free(temp);
			}
		}
		if (buf)
			r = read(fd, *buf, BUFFER_SIZE);
	}
	return (line);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	src_size;
	size_t	dst_size;

	src_size = 0;
	dst_size = 0;
	while (src[src_size])
		src_size++;
	if (dstsize != 0)
	{
		while (dst_size < dstsize - 1 && src[dst_size] != '\0')
		{
			dst[dst_size] = src[dst_size];
			dst_size++;
		}
		dst[dst_size] = '\0';
	}
	return (src_size);
}
