/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 09:54:01 by dneves-d          #+#    #+#             */
/*   Updated: 2026/06/08 09:54:04 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_len_numbers(long number)
{
	int	len;

	len = 0;
	if (number <= 0)
	{
		number = -number;
		len += 1;
	}
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

void	ft_char_nbr(long numb, char *nbr, int len_n)
{
	if (numb == 0)
	{
		nbr[0] = '0';
		nbr[1] = '\0';
	}
	if (numb < 0)
	{
		nbr[0] = '-';
		numb = -numb;
	}
	nbr[len_n] = '\0';
	while (numb > 0)
	{
		len_n--;
		nbr[len_n] = (numb % 10) + '0';
		numb /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*nbr;
	int		len_n;
	long	numb;

	len_n = 0;
	numb = n;
	len_n = ft_len_numbers(numb);
	nbr = malloc((len_n + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	ft_char_nbr(numb, nbr, len_n);
	return (nbr);
}
