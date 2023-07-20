/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulorod <paulorod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:17:25 by paulorod          #+#    #+#             */
/*   Updated: 2023/04/26 13:42:21 by paulorod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Get word count and characters in string*/
static void	get_word_count(char const *s, char c,
	size_t *letters, size_t *words)
{
	bool	is_word;

	*letters = 0;
	*words = 0;
	is_word = false;
	while (*s)
	{
		if (*s != c)
		{
			if (!is_word)
			{
				(*words)++;
				is_word = true;
			}
			(*letters)++;
		}
		else
			is_word = false;
		s++;
	}
}

/*Clear array and buffer*/
static void	*clear_array(char **array, char *buffer, size_t size)
{
	if (array)
	{
		while (size > 0)
		{
			free(array[--size]);
		}
		if (size == 0)
			free(array);
	}
	if (buffer)
		free(buffer);
	return (NULL);
}

/*Add words to buffer*/
static void	fill_buffers(const char *str,
	const char c, char **array, char *buffer)
{
	bool	is_on_word;

	is_on_word = false;
	while (*str)
	{
		if (*str != c)
		{
			*buffer = *str;
			if (!is_on_word)
			{
				is_on_word = true;
				*array++ = buffer;
			}
			buffer++;
		}
		else
		{
			if (is_on_word)
			{
				*buffer++ = '\0';
				is_on_word = false;
			}
		}
		str++;
	}
}

/*Allocates and returns an array of strings obtained by splitting ’s’
using the character ’c’ as a delimiter.
The array must end with a NULL pointer.*/
char	**ft_split(char const *s, char c)
{
	size_t	words;
	size_t	letters;
	char	**array;
	char	**tmp;
	char	*buffer;

	get_word_count(s, c, &letters, &words);
	array = ft_calloc(sizeof(char *), words + 1);
	if (!array)
		return (NULL);
	buffer = ft_calloc(sizeof(char), letters + words);
	if (!buffer)
		return (clear_array(array, buffer, 0));
	array[words] = NULL;
	fill_buffers(s, c, array, buffer);
	tmp = array;
	while (*tmp)
	{
		*tmp = ft_strdup(*tmp);
		if (!*tmp)
			return (clear_array(array, buffer, tmp - array));
		tmp++;
	}
	free(buffer);
	return (array);
}
