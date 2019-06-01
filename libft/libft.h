/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 11:10:09 by omulder        #+#    #+#                */
/*   Updated: 2019/05/31 14:37:07 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_printf.h"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

char				*ft_itoa(int n);
char				*ft_strdup(const char *s1);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnew(size_t size);
char				*ft_strreplace(char *str, char *find, char *replace);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
int					ft_atoi(const char *str);
size_t				ft_strlen(const char *s);
void				*ft_memalloc(size_t size);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
void				ft_memdel(void **as);
void				ft_putstrarr(char **arr);
void				ft_putstrarri(char **arr);
void				ft_strdel(char **as);
int					ft_isdigit(int c);
int					ft_isspace(int c);
int					ft_intlen(int n);
void				*ft_memcpy(void *dst, void *src, size_t n);
void				ft_putendl(char const *s);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strstr(const char *haystack, const char *needle);
void				ft_putchar(unsigned int c);
void				ft_bzero(void *s, size_t n);
int					ft_isblank(char c);
char				*ft_strjoinfree(char *s1, char *s2, int i);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isprint(int c);
char				*ft_strcdup(char *str, char c);
void				ft_freearray(char ***array_p);
int					ft_arraylen(char **array);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
t_list				*ft_lstnew(void *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
char				*ft_strndup(const char *s1, size_t n);
int					ft_strequ(char const *s1, char const *s2);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					ft_lstlen(t_list *lst);
char				**ft_lsttoarray(t_list *lst);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstaddback(t_list *alst, t_list *new);
t_list				*ft_lstnew(void *content, size_t content_size);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
char				*ft_strchr(const char *s, int c);
char				**ft_strsplit(const char *s, char c);
char				*ft_strjoinchr(char const *s1, char c);
char				*ft_strjoinchrfree(char *s1, char c, int i);
int					ft_strarradd(char ***arr, char *add); // Not sure if this func is save2use
void				ft_strarrdel(char ***arr);

#endif
