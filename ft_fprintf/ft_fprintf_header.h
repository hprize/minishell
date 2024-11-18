/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_header.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyebinle <hyebinle@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:05:21 by ihyebin           #+#    #+#             */
/*   Updated: 2024/08/03 18:08:47 by hyebinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FPRINTF_HEADER_H
# define FT_FPRINTF_HEADER_H

# include <stdarg.h>
# include <fcntl.h>
# include "../libft/libft.h"

int		ft_fprintf(int fd, char *str, ...);
void	ft_fputstr_print(int fd, char *s, int *cnt);
void	ft_fputchar(int fd, char c, int *cnt);
void	ft_fputnbr(int fd, int n, int *cnt);
void	ft_fu_putnbr(int fd, unsigned int n, int *cnt);
void	ft_fput_hex(int fd, unsigned int n, int *cnt);
void	ft_fput_l_hex(int fd, unsigned int n, int *cnt);
void	ft_fput_long_hex(int fd, unsigned long n, int *cnt);

#endif
