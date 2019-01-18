/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oivanyts <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:37:23 by oivanyts          #+#    #+#             */
/*   Updated: 2018/11/24 11:24:26 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <float.h>
# include "../libft/includes/libft.h"

typedef struct {
	char			flag[5];
	int				whidth;
	int				precs;
	char			mods;
	char			type;
}					t_format;

union				u_some{
	char			str[16];
	double			d;
	long double		l_d;
	long long int	l_i;
}					u_ni;

extern const char	*g_colortab[9];

int					ft_max_number(int a, int b, int c);
int					ft_printf(const char *format, ...);
char				*ft_strnum_base(unsigned long long int n, int base,
		t_format fx);
size_t				ft_strlen_u(wchar_t *str);
char				*ft_itoa_prntf(long long int n, t_format fx);
char				*ft_itoa_double(long double num, t_format fx);
long double			ft_round_double(long double num, int precision);
long double			ft_exp(int num, int exp);
int					ft_putchar_u(int c, int fd);
int					ft_putstr_u(wchar_t *s, int fd);
wchar_t				*ft_strndup_u(wchar_t *src, size_t n);
int					ft_charlen(wchar_t c);
int					ft_parcer_printf(const char **str, va_list arg, int fd);
void				zero_struct(t_format *list);
int					formated_print(va_list arg, t_format fx, int fd);
int					format_char(va_list arg, t_format fx, int fd);
char				*form_numbers(va_list arg, t_format fx);
char				*ft_printbits(char *str, t_format fx);
char				*ft_check_color(const char *str);
void				ft_color_input(char *color);
int					ft_printf_fd(int fd, const char *format, ...);

#endif
