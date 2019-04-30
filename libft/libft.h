/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbrinksm <jbrinksm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/09 11:10:09 by omulder        #+#    #+#                */
/*   Updated: 2019/04/30 10:32:20 by tde-jong      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "ft_printf.h"

char			*ft_itoa(int n);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strnew(size_t size);
char			*ft_strreplace(char *str, char *find, char *replace);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
void			*ft_memalloc(size_t size);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_memdel(void **as);
void			ft_putstrarr(char **arr);
void			ft_putstrarri(char **arr);
void			ft_strdel(char **as);
int				ft_isdigit(int c);
int				ft_isspace(int c);
int				ft_intlen(int n);
void			*ft_memcpy(void *dst, void *src, size_t n);
void			ft_putendl(char const *s);
void			ft_putstr(char const *s);
void			ft_putnbr(int n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strstr(const char *haystack, const char *needle);
void			ft_putchar(unsigned int c);
void			ft_bzero(void *s, size_t n);
int				ft_isblank(char c);
char			*ft_strjoinfree(char *s1, char *s2, int i);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isprint(int c);
char			*ft_strcdup(char *str, char c);
void			ft_freearray(char ***array_p);
int				ft_arraylen(char **array);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strequ(char const *s1, char const *s2);

#endif
