/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strjoin.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ihyebin <ihyebin@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/29 16:58:17 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/04 03:09:45 by ihyebin		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*arr;

	arr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!arr)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
	{
		arr[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		arr[i + j] = s2[j];
		j++;
	}
	arr[i + j] = '\0';
	return (arr);
}
