/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstclear_bonus.c								:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: hyebinle <hyebinle@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/03/02 13:51:44 by ihyebin		   #+#	#+#			 */
/*   Updated: 2024/03/03 18:10:54 by hyebinle		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*next;

	curr = *lst;
	if (!lst | !*lst)
		return ;
	while (curr)
	{
		next = curr->next;
		ft_lstdelone(curr, del);
		curr = next;
	}
	*lst = NULL;
}
