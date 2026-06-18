/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:39:24 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/27 16:00:00 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write(unsigned char *dest, const unsigned char	*src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest > src)
	{
		while (n > 0)
		{
			n--;
			dest[n] = src[n];
		}
	}
	else
	{
		while (i < n)
		{
			dest[i] = src[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*sc;

	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	dt = (unsigned char *)dest;
	sc = (const unsigned char *)src;
	ft_write(dt, sc, n);
	return (dest);
}
