/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 05:00:23 by ihyebin           #+#    #+#             */
/*   Updated: 2024/08/03 18:15:48 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf_header.h"

static void	check_conversion(int fd, char c, va_list *ap, int *cnt);

int	ft_fprintf(int fd, char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	va_start(ap, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '%')
		{
			ft_fputchar(fd, str[i], &count);
			i++;
		}
		if (str[i] == '%')
		{
			check_conversion(fd, str[++i], &ap, &count);
			i++;
		}
	}
	va_end(ap);
	return (count);
}

static void	check_conversion(int fd, char c, va_list *ap, int *cnt)
{
	if (c == 'c')
		ft_fputchar(fd, (char)va_arg(*ap, int), cnt);
	else if (c == '%')
		ft_fputchar(fd, '%', cnt);
	else if (c == 's')
		ft_fputstr_print(fd, va_arg(*ap, char *), cnt);
	else if (c == 'd')
		ft_fputnbr(fd, va_arg(*ap, int), cnt);
	else if (c == 'p')
		ft_fput_long_hex(fd, (unsigned long)va_arg(*ap, void *), cnt);
	else if (c == 'i')
		ft_fputnbr(fd, va_arg(*ap, int), cnt);
	else if (c == 'u')
		ft_fu_putnbr(fd, va_arg(*ap, unsigned int), cnt);
	else if (c == 'x')
		ft_fput_hex(fd, va_arg(*ap, unsigned int), cnt);
	else if (c == 'X')
		ft_fput_l_hex(fd, va_arg(*ap, unsigned int), cnt);
}
