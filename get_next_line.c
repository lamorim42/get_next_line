/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lamorim <lamorim@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 10:57:44 by lamorim           #+#    #+#             */
/*   Updated: 2021/09/13 14:37:46 by lamorim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_strjoin(const char *s1, const char *s2);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_len_to_n(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*get_one_line(const char *buf, char **save_buf, char *line1);

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*save_buf = NULL;
	char		*line;
	char		*temp;
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
	while (r > 0)
	{
		if (ft_strchr(buf, '\n'))
		{
			line = get_one_line(buf, &save_buf, line);
			free(buf);
			return (line);
		}
		else
		{
			if (!save_buf)
				save_buf = ft_substr(buf, 0, BUFFER_SIZE);
			else
			{
				temp = save_buf;
				save_buf = ft_strjoin(save_buf, buf);
				free(temp);
			}
		}
		r = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
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

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	s2_len = 0;
	while (s2[s2_len])
		s2_len++;
	join = (char *) malloc(s1_len + s2_len + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, (char *) s1, s1_len + 1);
	ft_strlcpy(join + s1_len, (char *) s2, s2_len + 1);
	return (join);
}

char	*ft_strchr(const char *s, int c)
{
	if (c == 0)
	{
		while (*s)
			s++;
		return ((char *)s);
	}
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return ((char *) '\0');
}

size_t	ft_len_to_n(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*s_cpy;
	size_t	s_len;

	s_len = 0;
	while (s[s_len])
		s_len++;
	s_cpy = (char *) malloc(s_len + 1);
	if (!s_cpy)
		return (NULL);
	while (s_len)
	{
		*s_cpy++ = *s++;
		s_len--;
	}
	s_cpy[s_len] = '\0';
	return (s_cpy);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_cpy;
	unsigned char	*src_cpy;

	if ((!dest && !src) || !n)
		return (dest);
	dest_cpy = (unsigned char *)dest;
	src_cpy = (unsigned char *)src;
	while (n--)
		*dest_cpy++ = *src_cpy++;
	return (dest);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			len_s;
	char			*sub_s;

	if (!s)
		return (NULL);
	len_s = 0;
	while (s[len_s])
		len_s++;
	if (start > len_s)
		return (ft_strdup(""));
	if (len_s < len)
		len = len_s - start;
	sub_s = (char *) malloc(len + 1);
	if (!sub_s)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[len] = '\0';
	return (sub_s);
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
