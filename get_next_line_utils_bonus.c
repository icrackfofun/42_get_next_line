/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:22:34 by psantos-          #+#    #+#             */
/*   Updated: 2025/04/30 14:53:28 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_valread(char **string, ssize_t bytes, char *arr)
{
	if (bytes < (ssize_t)0)
	{
		*arr = '\0';
		free(*string);
		*string = NULL;
		return (NULL);
	}
	if (*string)
		return (*string);
	return (NULL);
}

char	*ft_findnl(char *arr)
{
	size_t		i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == '\n')
		{
			return (&arr[i]);
		}
		i++;
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize > 0)
	{
		i = 0;
		while (src[i] && i < dstsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_linelen(src));
}

void	ft_buffercpy(char **ptr, char *arr)
{
	char	*temp;
	size_t	len_ptr;
	size_t	len_arr;

	len_arr = ft_linelen(arr);
	len_ptr = 0;
	if (*ptr)
		len_ptr = ft_strlen(*ptr);
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
		temp = NULL;
	}
	ft_strlcpy(*ptr + len_ptr, arr, len_arr + 1);
}

void	ft_trimbuffer(char *arr)
{
	int	i;

	i = 0;
	while (arr[i] && arr[i] != '\n')
		i++;
	if (arr[i] == '\n')
		i++;
	ft_strlcpy(arr, arr + i, ft_strlen(arr + i) + 1);
}
