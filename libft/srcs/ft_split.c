/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qsomarri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:59:52 by qsomarri          #+#    #+#             */
/*   Updated: 2024/08/22 17:31:20 by qsomarri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_str(const char *s, char c)
{
	size_t	i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static char	*ft_str_index_cpy(const char *s, int index, char c)
{
	size_t	i;
	char	*dest;

	i = 0;
	while (s[index + i] && s[index + i] != c)
		i++;
	dest = (char *)malloc(sizeof(const char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[index + i] && s[index + i] != c)
	{
		dest[i] = s[index + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static	char	**ft_makesplit(char **dest, const char *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
		{
			dest [j] = ft_str_index_cpy(s, i, c);
			if (!dest[j])
			{
				ft_free_tab(dest);
				return (NULL);
			}
			j++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(const char *s, char c)
{
	size_t	len;
	char	**dest;

	len = ft_count_str(s, c);
	dest = (char **)malloc(sizeof(const char *) * (len + 1));
	if (dest == NULL)
		return (NULL);
	dest = ft_makesplit(dest, s, c);
	return (dest);
}
