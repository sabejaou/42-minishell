/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:30:57 by anfichet          #+#    #+#             */
/*   Updated: 2023/11/24 17:32:05 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h> /*write function*/
# include <stdlib.h> /*malloc-free function*/
# include <stddef.h> /*size_t*/
# include <limits.h> /*int max- min max*/
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

char	**ft_split(char const *s, char c);
char	**ft_split_whitespace(char const *s);
char	*ft_itoa(int n);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
int		ft_isalnum(int i);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int i);
int		ft_isprint(int c);
int		ft_lstsize(t_list *lst);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
size_t	ft_protect_strlen(const char *str);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t size);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_strcmp(const char *s1, const char *s2);

/*GET_NEXT_LINE*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
size_t	ft_strlen_gnl(const char *str, int c);
char	*ft_strjoin_gnl(char *s1, const char *s2, size_t *n);
char	*ft_strdup_gnl(const char *src);
void	*ft_memmove_gnl(char *dest, const char *src, size_t n);
char	*get_empty_line(char *stash, size_t *n);
int		reading_line(int fd, char *stash, char **next_line, size_t *n);

/*FT_PRINTF*/
# define BASE16_LOWER "0123456789abcdef"
# define BASE16_UPPER "0123456789ABCDEF"
# define BASE10 "0123456789"

int		ft_dprintf(int fd, const char *format, ...);

int		ft_printf(const char *str, ...) __attribute__ ((format (printf, 1, 2)));
size_t	ft_strlen_pf(const char *str);
void	ft_putnbr_base(int nbr, char *base, int *addr_count);
void	ft_putchar_pf(char c, int *addr_count);
void	ft_putstr_pf(char *str, int *addr_count);
void	ft_unsigned_putnbr(unsigned long int nbr, char *base, int *addr_count);
size_t	ft_strlenpercent(const char *str);
void	ft_put_address(unsigned long int nbr, int *addr_count);
void	ft_print_format(const char specifier, va_list arg, int *addr_count);
void	ft_print_first_arg(const char *str, size_t *addr_i, int *addr_count);
void	ft_print(int *addr_count, const char *str, size_t *addr_i, va_list arg);
int		is_specifier(char c);
void	check_percent(const char *str, int *addr_count, size_t *addr_i);

#endif