/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:34:03 by hyebinle          #+#    #+#             */
/*   Updated: 2024/08/03 18:09:49 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf_header.h"

void	ft_fput_hex(int fd, unsigned int n, int *cnt)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (n > 15)
		ft_fput_hex(fd, n / 16, cnt);
	ft_fputchar(fd, hex[n % 16], cnt);
}

void	ft_fput_l_hex(int fd, unsigned int n, int *cnt)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (n > 15)
		ft_fput_l_hex(fd, n / 16, cnt);
	ft_fputchar(fd, hex[n % 16], cnt);
}

static int	count_digits(unsigned long n)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n /= 16;
		count++;
	}
	return (count);
}

void	ft_fput_long_hex(int fd, unsigned long n, int *cnt)
{
	char	*hex;
	char	*arr;
	int		count;

	if (n == 0)
	{
		ft_fputstr_print(fd, "(nil)", cnt);
		return ;
	}
	hex = "0123456789abcdef";
	count = count_digits(n);
	arr = (char *)malloc(sizeof(char) * (count + 3));
	if (!arr)
		return ;
	arr[0] = '0';
	arr[1] = 'x';
	arr[count + 2] = '\0';
	while (n > 15)
	{
		arr[--count + 2] = hex[n % 16];
		n /= 16;
	}
	arr[count + 1] = hex[n];
	ft_fputstr_print(fd, arr, cnt);
	free(arr);
}
