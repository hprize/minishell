/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_striteri.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/01 15:42:00 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/03 18:13:21 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
