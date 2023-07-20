/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 15:02:22 by paulorod          #+#    #+#             */
/*   Updated: 2023/05/23 15:08:47 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Join buffers together*/
static char	*join_buffers(char *buffer1, char *buffer2)
{
	char	*tmp;

	tmp = ft_strjoin(buffer1, buffer2);
	free(buffer1);
	buffer1 = NULL;
	if (!tmp)
		return (NULL);
	return (tmp);
}

/*Get full line*/
static char	*read_to_buffer(char *buffer, int fd)
{
	char	*tmp;
	int		read_bytes;

	tmp = ft_calloc(sizeof(char), GNL_BUFFER_SIZE + 1);
	if (!tmp)
		return (ft_free(buffer));
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, tmp, GNL_BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(tmp);
			return (ft_free(buffer));
		}
		tmp[read_bytes] = '\0';
		buffer = join_buffers(buffer, tmp);
		if (!buffer)
			return (ft_free(tmp));
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	free(tmp);
	return (buffer);
}

/*Get a line from the buffer*/
static char	*get_line_from_buffer(char *buffer)
{
	char	*line;
	int		i;
	int		l_size;

	i = 0;
	l_size = 1;
	if (!buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		l_size = 2;
	line = ft_calloc(sizeof(char), i + l_size);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i] = buffer[i];
	return (line);
}

/*Advance the buffer to the next line*/
static char	*advance_buffer_to_next_line(char *buffer)
{
	char	*line;
	int		l_size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	l_size = ft_strlen(buffer);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free(buffer));
	line = ft_calloc(sizeof(char), l_size - i + 1);
	if (!line)
		return (ft_free(buffer));
	i++;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	if (!line[0])
		return (ft_free(line));
	return (line);
}

/*Gets the next line in the file pointed by 'fd'*/
char	*get_next_line(int fd)
{
	static char	*buffer[1000];
	char		*line;

	if (fd < 0 || fd > 1000 || GNL_BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(sizeof(char), 1);
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = read_to_buffer(buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line = get_line_from_buffer(buffer[fd]);
	buffer[fd] = advance_buffer_to_next_line(buffer[fd]);
	return (line);
}
