/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:13:44 by ddzuba            #+#    #+#             */
/*   Updated: 2023/04/13 16:31:44 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdio.h>

# define BUFFER_SIZE	42

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *srs, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *srs, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strchr(const char *s, int d);
char	*ft_strrchr(const char *s, int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
t_list	*ft_lstlast(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* GNL functions */

size_t	gnl_strlen(char *str);
char	*gnl_strchr(char *str, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*ft_take_line(char *temp);
char	*ft_hold_line(char *temp);
char	*ft_read_line_and_save(int fd, char *temp);
char	*get_next_line(int fd);

/* Additional functions */

int		ft_flname_extens_cmp(char *name, char *end);
int		ft_table_linecount(char **table);
void	ft_free_table(char	**table);
int		ft_strlen_int(const char *s);
void	*ft_free(void *data);
int		ft_memcpm_reverse(char *s1, char *s2);
int		ft_if_empty_line(char *line);
char	**ft_split_charset(char *str, char *set);
void	*ft_clear_split(char **split);
void	*ft_free_split(char **split);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy_complete(char *dest, char *src, char charset, int len);
int		*ft_realloc_int(int *tab, int len_tab, int add_len);
char	**ft_realloc_one(char **old, int len, char *new_line);
char	*realloc_set(char *line, int new_len, char charset);
int		ft_absolute_value(float x);
char	*ft_strjoinf(char *s1, char *s2, int to_free);

/* fd_printf functions */

int		ft_dprintf(int fd, const char *format, ...);
int		ft_vdprintf(int fd, const char *format, va_list args);
char	*ft_vasprintf(const char *format, va_list args);
int		ft_vsnprintf(char *str, size_t size, const char *format, va_list args);

#endif