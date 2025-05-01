/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:51:30 by psantos-          #+#    #+#             */
/*   Updated: 2025/04/30 13:53:21 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*string;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	string = NULL;
	bytes_read = ft_strlen(buffer);
	if (buffer[0] == '\0')
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (!ft_findnl(buffer) && bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		ft_buffercpy(&string, buffer);
		ft_trimbuffer(buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read <= 0)
		return (ft_valread(&string, bytes_read, buffer));
	buffer[bytes_read] = '\0';
	ft_buffercpy(&string, buffer);
	ft_trimbuffer(buffer);
	return (string);
}

/*void run_test(const char *filename)
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
	//run_test("empty.txt");                 // Empty file
	//run_test("one_line.txt");              // One line with newline
	//run_test("one_line_no_nl.txt");        // One line without newline
	//run_test("multi_lines.txt");           // Multiple lines
	//run_test("only_newlines.txt");         // File with only \n characters
	//run_test("long_line.txt");             // A single long line > BUFFER_SIZE
	run_test("mixed_newlines.txt");        // Newlines in weird spots
	//run_test("ends_no_nl.txt");            // Last line has no \n*/

/*	return (0);
}*/
