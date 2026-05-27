/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 10:39:24 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/27 09:34:41 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write(unsigned char *dt, const unsigned char	*dtv, size_t n)
{
	size_t	i;

	i = 0;
	if (dt > dtv)
		{
			while (n > 0)
			{
				dt[n] = dtv[n];
				n--;
			}
		}
		else
		{
			while (i < n)
			{
				dt[i] = dtv[i];
				i++;
			}
		}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dt;
	const unsigned char	*dtv;

	if (!dest && !src)
		return (NULL);
	dt = (unsigned char *)dest;
	dtv = (const unsigned char *)src;
	ft_write(dt, dtv, n);
	return (dt);
}
