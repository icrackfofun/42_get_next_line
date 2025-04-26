/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:13:47 by psantos-          #+#    #+#             */
/*   Updated: 2025/04/26 19:23:44 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	size_t		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if (str[i] == '\0')
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

void	ft_buffercpy(char **ptr, char *arr)
{
	char	*temp;
	size_t	len_ptr;
	size_t	len_arr;

	len_ptr = *ptr ? ft_strlen(*ptr) : 0;
	len_arr = ft_strlen(arr);
	temp = *ptr;
	*ptr = malloc(len_ptr + len_arr + 1);
	if (!*ptr)
	{
		free(temp);
		*ptr = NULL;
		return ;
	}
	if (temp)
	{
		ft_strlcpy(*ptr, temp, len_ptr + 1);
		free(temp);
	}
	ft_strlcpy(*ptr + len_ptr, arr, len_arr + 1);
}

void ft_trimbuffer(char *arr)
{
    int i = 0;
    int j = 0;

    while (arr[i] && arr[i] != '\n')
        i++;
    if (arr[i] == '\n')
        i++;
    while (arr[i])
    {
        arr[j++] = arr[i++];
    }
	while (j <= BUFFER_SIZE + 2)
    	arr[j++] = '\0';
}

char *ft_return(char **ptr, char *arr, size_t read_bytes)
{
	if (read_bytes == (size_t)-1)
	{
		free(*ptr);
		*ptr = NULL;
		return (*ptr);
	}
	if (read_bytes == 0)
		return (*ptr);
	ft_buffercpy(ptr, arr);
	ft_trimbuffer(arr);
	return (*ptr);
}
