/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstiter_bonus.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/02 16:49:41 by ihyebin		   #+#	#+#			 */
/*   Updated: 2024/03/03 18:10:39 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
