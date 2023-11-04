/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:48:11 by otawatanabe       #+#    #+#             */
/*   Updated: 2023/11/03 17:07:03 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*concat(char *s1, char *s2, ssize_t l2)
{
	char	*ret;
	ssize_t	l1;
	ssize_t flag;

	l1 = 0;
	flag = l2;
	if (s2 == NULL || l2 == 0)
		return (s1);
	while ((s1 && s1[l1] && ++l1) || (flag == -1 && s2[++l2]))
		;
	ret = malloc(l1 + l2 + 1);
	if (ret == NULL)
	{
		free(s1);
		return (NULL);
	}
	ret[l1 + l2] = '\0';
	while (l2--)
		ret[l1 + l2] = s2[l2];
	while (++l2 < l1)
		ret[l2] = s1[l2];
	free(s1);
	if (flag == -1)
		free(s2);
	return (ret);
}

int	check_new_line(char *s, char **line, ssize_t max)
{
	ssize_t	size;
	ssize_t	i;

	size = 0;
	if (max != -1)
		s[max] = '\0';
	while (s[size] && (!size || s[size - 1] != '\n'))
		size++;
	*line = concat(*line, s, size);
	if (*line == NULL)
	{
		free(s);
		s = NULL;
		return (0);
	}
	if (s[size - 1] != '\n')
		return (1);
	i = 0;
	while (s[size + i++])
		s[i - 1] = s[size + i - 1];
	s[i - 1] = '\0';
	return (0);
}

char	*buf_read(char **buf, int fd, char **rest)
{
	ssize_t	num_read;
	char	*line;

	line = NULL;
	num_read = read(fd, *buf, BUFFER_SIZE);
	while (num_read > 0 && check_new_line(*buf, &line, num_read))
		num_read = read(fd, *buf, BUFFER_SIZE);
	if (num_read > 0 && line && **buf)
	{
		*rest = *buf;
		*buf = NULL;
	}
	if (num_read == -1 || line == NULL || *line == '\0')
	{
		free(line);
		line = NULL;
	}
	return (line);
}
