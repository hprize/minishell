/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strncmp.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/26 17:38:52 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/03 18:13:37 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u1;
	unsigned char	*u2;

	u1 = (unsigned char *)s1;
	u2 = (unsigned char *)s2;
	i = 0;
	while ((u1[i] || u2[i]) && i < n)
	{
		if (u1[i] == u2[i])
			i++;
		else
			return ((u1[i] - u2[i]));
	}
	return (0);
}
