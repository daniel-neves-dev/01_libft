/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <dneves-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 15:43:34 by dneves-d          #+#    #+#             */
/*   Updated: 2026/05/28 16:34:37 by dneves-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_letter;

	last_letter = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			last_letter = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (last_letter);
}
