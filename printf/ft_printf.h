/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:21:16 by pborrull          #+#    #+#             */
/*   Updated: 2023/10/19 09:55:35 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
int		ft_printf_i(int n);
int		ft_printf_p(unsigned long p);
int		ft_printf_s(char *s);
int		ft_printf_u(int n);
int		ft_printf_x(unsigned int n);
int		ft_printf_xx(int n);
int		ft_printchar(char c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
int		ft_while(const char *s, int i, int t, va_list list);
char	*ft_strchr(const char *s, int d);
int		ft_wall_if(va_list list, char c);

#endif
