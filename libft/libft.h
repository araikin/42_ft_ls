/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asultanb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:11:33 by asultanb          #+#    #+#             */
/*   Updated: 2020/01/12 14:47:16 by asultanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>

# define BUFF_SIZE 32

# define MINUS	1
# define ZERO	2
# define PLUS	4
# define HASH	8
# define SPACE	16

# define L		1
# define LL		2
# define H		4
# define HH		8
# define UL		16

# define SPECS	"cspdDiouxXf%"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_format
{
	int				length : 5;
	int				flags : 5;
	int				prec;
	int				width;
	int				p_rem;
	int				w_rem;
	char			spec;
}					t_format;

typedef int			t_specifiers(va_list *argp, t_format *data);

int					ft_printf(const char *format, ...);
int					print_format(char c);
int					clear_format(t_format *data);
t_format			*initialize_format(void);

int					parse_format(va_list *argp, char *format, int *i);
void				set_params(t_format *data, char *format, int *i);
char				*get_all_params(char *format, int i);
int					apply_params(va_list *argp, t_format *data);

void				set_flags(char *params, t_format *data, int *pos);
void				set_width(char *params, t_format *data, int *pos);
void				set_precision(char *params, t_format *data, int *pos);
void				set_length(char *params, t_format *data, int *pos);
void				set_specifier(char *params, t_format *data, int *pos);

int					is_flag(char c);
int					is_specifier(char c);
int					is_digit(char c);
int					is_length(char *params, int i);

int					handle_c(va_list *argp, t_format *data);
int					handle_s(va_list *argp, t_format *data);
void				adjust_p(t_format *data, char *str);
int					handle_p(va_list *argp, t_format *data);
int					handle_percent(va_list *argp, t_format *data);

int					adjust_di(t_format *data, int64_t n, int len);
int					handle_di(va_list *argp, t_format *data);
void				print_sign(t_format *data, int64_t n, int m, char flag);
void				di_minus(t_format *data, int64_t n);
void				di_nominus(t_format *data, int64_t n);

void				print_ox(t_format *data, uint64_t n);
void				ouxx_minus(t_format *data, uint64_t n, int base, char flag);
void				ouxx_nomin(t_format *data, uint64_t n, int base, char flag);
int					adjust_ouxx(t_format *data, uint64_t n, int len, int base);
int					handle_ouxx(va_list *argp, t_format *data);

int					handle_f(va_list *argp, t_format *data);
int					f_prec(t_format *data, int len, long double f, int sign);
void				print_f_prec(t_format *data, long double f);
int					f_prec_zero(t_format *data, long long int n, int sign,
					int len);
void				print_fraction(t_format *data, float f, int sign);

char				*itoa_base(unsigned long long n, int base, char c);
void				putnbr_ll(char specifier, unsigned long long n, int base);
void				print_rem(int rem, char c);
int					ft_numlen(unsigned long long n, int base);
long double			get_round(int precision);

int					ft_min(int a, int b);
int					ft_max(int a, int b);
int					ft_abs(int n);

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle, \
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
long long			ft_atoll(char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

void				ft_lstpush(t_list **alst, t_list *new);
t_list				*ft_strsplit_lst(char const *s, char c);
void				ft_lstprint(t_list *lst);
char				*ft_itoa_base(int n, int base);
t_list				*ft_lstfind(t_list *lst, void *data, int (*cmp)());

int					get_next_line(const int fd, char **line);

void				bubble_sort(int *arr, int size);
#endif
