/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strtrim.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/11 02:51:09 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/03/11 02:51:11 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		end;
	int		start;
	int		malc_len;
	char	*arr;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	end = ft_strlen(s1) - 1;
	start = 0;
	while (s1[end] && is_set(s1[end], set) && end >= 0)
		end--;
	if (end < 0)
		return (ft_strdup(""));
	while (s1[start] && is_set(s1[start], set) && start < end)
		start++;
	malc_len = end - start + 1;
	arr = (char *)malloc(sizeof(char) * malc_len + 1);
	if (!arr)
		return (0);
	ft_strlcpy(arr, s1 + start, malc_len + 1);
	return (arr);
}

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}
// char	*ft_strtrim(char const *s1, char const *set)
// {
// 	int i = 0;
// 	int j = ft_strlen((char *)s1) - 1;
// 	char	*arr;

// 	if (s1 == NULL)
// 		return (NULL);
// 	if (set == NULL)
// 		return (ft_strdup(s1));
// 	while (s1[i] && ft_strchr(set, s1[i]))
// 		++i;
// 	while (j > i && ft_strchr(set, s1[j]))
// 		--j;
// 	arr = ft_substr(s1, i, (j - i +1));
// 	if (!arr)
// 		return (0);
// 	return (arr);
// }
