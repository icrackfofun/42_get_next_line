/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:40:40 by psantos-          #+#    #+#             */
/*   Updated: 2025/04/24 17:43:32 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!str)
		return (NULL);
	ft_strlcpy((char *)str, s1, ft_strlen(s1) + 1);
	ft_strlcpy((char *)&str[ft_strlen(s1)], s2, ft_strlen(s2) + 1);
	return (str);
}

char	*ft_return_string(char **stash, char *string, char *temp)
{
	char	*newline_pos;

	newline_pos = ft_strchr(*stash, '\n');
	if (newline_pos)
	{
		string = ft_calloc((newline_pos - *stash) + 2, 1);
		if (!string)
			return (NULL);
		ft_strlcpy(string, *stash, newline_pos - *stash + 2);
		temp = ft_strdup(newline_pos + 1);
		free(*stash);
		*stash = temp;
	}
	else
	{
		string = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
	return (string);
}

void	ft_stashjoin(char **stash, char *buffer, char *temp)
{
	if (!stash || !*stash)
		return ;
	temp = ft_strjoin(*stash, buffer);
	free (*stash);
	*stash = temp;
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*string;
	char			*temp;
	ssize_t			bytes_read;
	char			buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string = NULL;
	temp = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
    	buffer[bytes_read] = '\0';
		if (!stash)
        	stash = ft_calloc(1, 1); 
		ft_stashjoin(&stash, buffer, temp);
    	if (ft_strchr(stash, '\n'))
        	return (ft_return_string(&stash, string, temp));
    	bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == 0 && stash && *stash)
    	return (ft_return_string(&stash, string, temp));
return (NULL);
}

void run_test(const char *filename)
{
    char *line;
    int fd;
    int count = 1;

    printf("\n🧪 Testing file: %s\n", filename);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to open file");
        return;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("📌 Line %d: [%s]\n", count++, line);
        free(line);
    }
    close(fd);
    printf("✅ End of file: %s\n", filename);
}

int main(void)
{
    // Create or provide these test files beforehand
    run_test("empty.txt");                 // Empty file
    run_test("one_line.txt");              // One line with newline
    run_test("one_line_no_nl.txt");        // One line without newline
    run_test("multi_lines.txt");           // Multiple lines
    run_test("only_newlines.txt");         // File with only \n characters
    run_test("long_line.txt");             // A single long line > BUFFER_SIZE
    run_test("mixed_newlines.txt");        // Newlines in weird spots
    run_test("ends_no_nl.txt");            // Last line has no \n

    return (0);
}