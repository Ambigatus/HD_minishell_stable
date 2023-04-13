/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:30:43 by ddzuba            #+#    #+#             */
/*   Updated: 2023/04/13 16:37:45 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_strjoinf is a function that concatenates two strings s1 and s2 and returns
* a new string with the concatenated result. Additionally, the function frees
* the memory allocated for s1 before returning. This function is useful in cases
* where the user wants to concatenate two strings and also wants to free the
* memory of the first string at the same time, to avoid memory leaks. */
char	*ft_strjoinf(char *s1, char *s2, int flag)
{
    char *new_str;
    size_t len_s1;
    size_t len_s2;

    if (!s1 || !s2)
        return (NULL);
    len_s1 = ft_strlen(s1);
    len_s2 = ft_strlen(s2);
    new_str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
    if (!new_str)
        return (NULL);
    ft_memcpy(new_str, s1, len_s1);
    ft_memcpy(new_str + len_s1, s2, len_s2);
    new_str[len_s1 + len_s2] = '\0';
    if (flag == 1 || flag == 3)
        free(s1);
    if (flag == 2 || flag == 3)
        free(s2);
    return (new_str);
}

