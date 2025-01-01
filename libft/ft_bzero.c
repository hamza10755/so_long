/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbelaih <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:49:56 by hbelaih           #+#    #+#             */
/*   Updated: 2024/08/29 14:02:22 by hbelaih          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include	"libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*l;
	int				i;

	i = 0;
	l = s;
	while (n)
	{
		l[i] = 0;
		i++;
		n--;
	}
}