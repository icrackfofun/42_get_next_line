/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psantos- <psantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:23:12 by psantos-          #+#    #+#             */
/*   Updated: 2025/04/30 14:55:16 by psantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_findnl(char *arr);
size_t	ft_linelen(const char *str);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void	ft_buffercpy(char **ptr, char *arr);
void	ft_trimbuffer(char *arr);
char	*ft_valread(char **string, ssize_t bytes, char *arr);
char	*read_line(int fd, char **buffer);
void	*ft_memset(void *s, int c, size_t n);

#endif