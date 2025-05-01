/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:08:07 by psantos-          #+#    #+#             */
/*   Updated: 2025/05/01 09:56:28 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

size_t	ft_linelen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*read_line(int fd, char **buffer)
{
	char		*string;
	ssize_t		bytes_read;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	string = NULL;
	bytes_read = ft_strlen(*buffer);
	if ((*buffer)[0] == '\0')
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
	while (!ft_findnl(*buffer) && bytes_read > 0)
	{
		(*buffer)[bytes_read] = '\0';
		ft_buffercpy(&string, *buffer);
		ft_trimbuffer(*buffer);
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
	}
	if (bytes_read <= 0)
		return (ft_valread(&string, bytes_read, *buffer));
	(*buffer)[bytes_read] = '\0';
	ft_buffercpy(&string, *buffer);
	ft_trimbuffer(*buffer);
	return (string);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = malloc(BUFFER_SIZE + 1);
		if (!buffer[fd])
			return (NULL);
		ft_memset(buffer[fd], 0, BUFFER_SIZE + 1);
	}
	line = read_line(fd, &buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}

/*void	run_multi_fd_test(const char *file1, 
const char *file2, const char *file3)
{
	int		fd1 = open(file1, O_RDONLY);
	int		fd2 = open(file2, O_RDONLY);
	int		fd3 = open(file3, O_RDONLY);
	char	*line1 = NULL;
	char	*line2 = NULL;
	char	*line3 = NULL;
	int		line_count = 1;

	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
	{
		perror("Error opening one of the files");
		return;
	}

	printf("🧪 Interleaved FD test: %s | %s | %s\n", file1, file2, file3);

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		if (!line1 && !line2 && !line3)
			break;

		if (line1)
		{
			printf("📁 [%s] Line %d: %s", file1, line_count, line1);
			free(line1);
		}
		if (line2)
		{
			printf("📁 [%s] Line %d: %s", file2, line_count, line2);
			free(line2);
		}
		if (line3)
		{
			printf("📁 [%s] Line %d: %s", file3, line_count, line3);
			free(line3);
		}
		line_count++;
	}

	close(fd1);
	close(fd2);
	close(fd3);
	printf("\n");

	printf("✅ Finished interleaved test.\n");
}

int	main(void)
{
	run_multi_fd_test("mixed_newlines.txt", "multi_lines.txt", "long_line.txt");
	// You can swap or duplicate file names to test edge cases
	return (0);
}*/