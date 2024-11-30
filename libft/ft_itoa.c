/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_itoa.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/01 13:35:08 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/03 18:12:23 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static int	get_lenth(int n);

char	*ft_itoa(int n)
{
	int		len;
	long	l_n;
	char	*str;

	len = get_lenth(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = n + '0';
	l_n = (long)n;
	if (l_n < 0)
	{
		str[0] = '-';
		l_n *= -1;
	}
	str[len] = '\0';
	while (l_n)
	{
		str[--len] = (l_n % 10) + '0';
		l_n /= 10;
	}
	return (str);
}

static int	get_lenth(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}
