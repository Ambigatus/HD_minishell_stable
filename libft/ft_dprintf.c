/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:29:15 by ddzuba            #+#    #+#             */
/*   Updated: 2023/04/13 11:49:31 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	int			len;
	va_list		args;

	va_start(args, format);
	len = ft_vdprintf(fd, format, args);
	va_end(args);
	return (len);
}

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	int			len;
	char		*str;

	str = ft_vasprintf(format, args);
	len = ft_strlen(str);
	write(fd, str, len);
	free(str);
	return (len);
}

char	*ft_vasprintf(const char *format, va_list args)
{
	va_list		args_copy;
	char		*str;
	size_t		str_len;

	va_copy(args_copy, args);
	str_len = ft_vsnprintf(NULL, 0, format, args_copy);
	va_end(args_copy);
	str = malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	ft_vsnprintf(str, str_len + 1, format, args);
	return (str);
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list args)
{
	int			len;
	va_list		args_copy;

	va_copy(args_copy, args);
	len = vsnprintf(str, size, format, args_copy);
	va_end(args_copy);
	if (len < 0 || (size_t)len >= size)
		return (-1);
	return (len);
}
