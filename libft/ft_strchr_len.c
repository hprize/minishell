/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr_len.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42gyeongsan.	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/02/26 13:28:59 by hyebinle		  #+#	#+#			 */
/*   Updated: 2024/10/30 17:52:57 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

int	ft_strchr_len(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		else
			i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (0);
}
