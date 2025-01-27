/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaleh <amsaleh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:19:58 by amsaleh           #+#    #+#             */
/*   Updated: 2025/01/07 00:26:39 by amsaleh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ft_printf.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 4096

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}					t_list;

typedef struct s_split
{
	size_t	start;
	size_t	end;
}			t_split;

size_t			ft_strlcat(char *dst, char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *str);
size_t			ft_lstsize(t_list *lst);
size_t			ft_strncpy(char *dst, const char *src, size_t size);
int				ft_atoi(const char *str);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				get_digits_amount(int n);
int				putstr_range(const char *str, size_t start, size_t end);
int				ft_memcmp(const void *s1, const void *s2, size_t size);
int				ft_strncmp(const char *s1, const char *s2, size_t size);
int				ft_abs(int x);
ssize_t			find_newline(char *str);
int				ft_strcmp(const char *s1, const char *s2);
long			ft_atol(const char *str);
char			*ft_itoa(int n);
char			*ft_strnstr(char *big, char *little, size_t n);
char			*ft_strrchr(const char *str, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, size_t start, size_t len);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(size_t, char *));
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			free_array(void **arr);
void			*ft_bzero(void *src, size_t size);
void			*ft_calloc(size_t nitems, size_t size);
void			*ft_memchr(const void *src, int c, size_t n);
void			*ft_memcpy(void *dest, void *src, size_t size);
void			*ft_memmove(void *dest, void *src, size_t n);
void			*ft_memset(void *src, int c, size_t size);
char			*gnl_strjoin(char *s1, char *s2, int n);
char			*get_next_line(int fd);
char			*ft_strtok(char *s, char *delimiter);
char			*ft_strchr(const char *str, int c);
char			*ft_strdup(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(size_t, char));
char			**ft_split(const char *s, char c);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

#endif
