/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstsize_bonus.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/02 06:13:16 by ihyebin		   #+#	#+#			 */
/*   Updated: 2024/03/03 18:11:33 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}
