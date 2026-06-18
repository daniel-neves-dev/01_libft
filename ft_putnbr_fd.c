/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:58:12 by dneves-d          #+#    #+#             */
/*   Updated: 2026/06/09 11:58:14 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	numb;

	numb = n;
	if (numb < 0)
	{
		numb = -numb;
		ft_putchar_fd('-', fd);
	}
	if (numb > 9)
		ft_putnbr_fd(numb / 10, fd);
	ft_putchar_fd(numb % 10 + '0', fd);
}
