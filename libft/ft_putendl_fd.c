/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_putendl_fd.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/01 17:00:59 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/01 19:15:25 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	int	len;

	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}
