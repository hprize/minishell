/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:01:49 by hyebinle          #+#    #+#             */
/*   Updated: 2024/08/03 18:12:53 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf_header.h"

void	ft_fputchar(int fd, char c, int *cnt)
{
	write(fd, &c, 1);
	*cnt += 1;
}

void	ft_fputnbr(int fd, int n, int *cnt)
{
	long	num;

	num = (long)n;
	if (num < 0)
	{
		num *= -1;
		*cnt += 1;
		write(fd, "-", 1);
	}
	if (num > 9)
		ft_fputnbr(fd, num / 10, cnt);
	ft_fputchar(fd, num % 10 + '0', cnt);
}

void	ft_fu_putnbr(int fd, unsigned int n, int *cnt)
{
	if (n > 9)
		ft_fu_putnbr(fd, n / 10, cnt);
	ft_fputchar(fd, n % 10 + '0', cnt);
}

void	ft_fputstr_print(int fd, char *s, int *cnt)
{
	size_t	len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	*cnt += len;
	write(fd, s, len);
}
