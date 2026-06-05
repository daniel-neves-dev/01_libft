/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dneves-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:51:14 by dneves-d          #+#    #+#             */
/*   Updated: 2026/06/01 13:52:03 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_search_string(char const *s, int start, size_t len, char *string)
{
	size_t	i;

	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		string[i] = s[start + i];
		i++;
	}
	string[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*string;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
	{
		string = malloc(1 * sizeof(char));
		if (!string)
			return (NULL);
		string[0] = '\0';
		return (string);
	}
	if (len > len_s - start)
		len = len_s - start;
	string = malloc((len + 1) * sizeof(char));
	if (!string)
		return (NULL);
	ft_search_string(s, start, len, string);
	return (string);
}
