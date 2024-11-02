/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_substr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ihyebin <ihyebin@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/28 21:12:20 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/07/17 02:46:18 by ihyebin		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	str_len;
	size_t	i;

	str_len = ft_strlen(s);
	if (start > str_len)
		len = 0;
	else if (start + len > str_len)
		len = str_len - start;
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
