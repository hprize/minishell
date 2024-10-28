/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:03:08 by hyebinle          #+#    #+#             */
/*   Updated: 2024/03/03 18:12:08 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_op(char c);
static int	is_digit(char c);

int	ft_atoi(const char *nptr)
{
	int	minus;
	int	m_count;
	int	result;

	minus = 1;
	m_count = 0;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	while (*nptr && is_op(*nptr))
	{
		if (*nptr == '-')
			minus *= -1;
		m_count++;
		if (m_count > 1)
			return (0);
		nptr++;
	}
	while (*nptr && is_digit(*nptr))
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (minus * result);
}

static int	is_op(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
