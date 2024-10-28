/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:00:13 by hyebinle          #+#    #+#             */
/*   Updated: 2024/03/03 18:13:13 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_seper(char str, char c);
static int	word_count(char const *s, char c);
static char	*word_cpy(char const *s, char c);
static void	arr_free(char **s, int i);

char	**ft_split(char const *s, char c)
{
	int		count;
	int		i;
	char	**arr;

	count = word_count(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (0);
	arr[count] = (void *)0;
	i = -1;
	while (*s)
	{
		while (is_seper(*s, c) && *s)
			s++;
		if (!is_seper(*s, c) && *s)
		{
			arr[++i] = word_cpy(s, c);
			if (!arr[i])
				arr_free(arr, i);
		}
		while (!is_seper(*s, c) && *s)
			s++;
	}
	return (arr);
}

static int	is_seper(char str, char c)
{
	if (str == c)
		return (TRUE);
	else
		return (FALSE);
}

static int	word_count(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (is_seper(s[i], c) && s[i])
			i++;
		if (!is_seper(s[i], c) && s[i])
		{
			i++;
			count++;
		}
		while (!is_seper(s[i], c) && s[i])
			i++;
	}
	return (count);
}

static char	*word_cpy(char const*s, char c)
{
	int		i;
	int		w_len;
	char	*str;

	w_len = 0;
	while (!is_seper(s[w_len], c) && s[w_len])
		w_len++;
	str = (char *)malloc(sizeof(char) * (w_len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < w_len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	arr_free(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}
