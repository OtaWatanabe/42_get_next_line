/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:17:50 by otawatanabe       #+#    #+#             */
/*   Updated: 2023/11/02 05:55:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat(char *s1, char *s2, ssize_t l1, ssize_t l2)
{
	char	*ret;
	ssize_t	i;

	i = 0;
	ret = malloc(l1 + l2 + 1);
	if (ret == NULL)
		return (NULL);
	while (i++ < l1)
		ret[i - 1] = s1[i - 1];
	if (l1)
		free(s1);
	i = 0;
	while (i++ < l2)
		ret[i - 1 + l1] = s2[i - 1];
	ret[l1 + l2] = '\0';
	return (ret);
}

int	check_new_line(char *s, char **line, ssize_t *l, int max)
{
	ssize_t	size;
	ssize_t	i;

	size = 0;
	while (s[size] && (size == 0 || s[size - 1] != '\n'))
		size++;
	if (max > 0 && size > max)
		size = max;
	*line = concat(*line, s, *l, size);
	*l += size;
	if (*line == NULL)
	{
		free(s);
		s = NULL;
		return (0);
	}
	if (s[size - 1] != '\n')
		return (1);
	i = size;
	while (s[i++])
		s[i - 1 - size] = s[i - 1];
	s[i - 1 - size] = '\0';
	return (0);
}

int	buf_read(char **line, char *buf, int fd, ssize_t n, char **rest)
{
	ssize_t	num_read;
	ssize_t i;

	buf[BUFFER_SIZE] = '\0';
	i = n;
	num_read = read(fd, buf, BUFFER_SIZE);
	while (num_read > 0 && check_new_line(buf, line, &n, num_read))
		num_read = read(fd, buf, BUFFER_SIZE);
	if (num_read > 0 && *line)
	{
		i = (n - i - 1) % BUFFER_SIZE + 1;
		if (i == num_read || (i - 1 == num_read && buf[num_read - 1] == '\0'))
			return (0);
		free(*rest);
		*rest = concat(*rest, buf, 0, num_read - i);
		if (*rest)
			return(1);
	}
	if (num_read == 0)
		return(0);
	free(*line);
	*line = NULL;
	return (0);
}


char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*rest;
	ssize_t		n;

	n = 0;
	line = NULL;
	if (BUFFER_SIZE <= 0 || (rest && check_new_line(rest, &line, &n, -1) == 0))
		return (line);
	if ((buf = malloc(BUFFER_SIZE + 1)) == NULL)
	{
		free(line);
		line = NULL;
	}
	if (buf == NULL || buf_read(&line, buf, fd, n, &rest) == 0)
	{
		free(rest);
		free(buf);
		rest = NULL;
		return (line);
	}
	free(buf);
	return (line);
}
