/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qr_sqrt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:48:05 by souaguen          #+#    #+#             */
/*   Updated: 2024/10/27 14:01:55 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double	ft_qrsqrt(double nbr)
{
	long	i;	
	float	y;
	float	x;
	float	threehalf;

	threehalf = 1.5f;
	x = nbr * 0.5f;
	y = nbr;
	i = *(long *) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float *) &i;
	y = y * (threehalf - (x * y * y));
	return (y);
}

int	main(int argc, char **argv)
{
	int	nbr;

	if (argc != 2)
		return (1);
	nbr = atoi(argv[1]);
	printf("%f => %f\n", sqrt(nbr), 1 / ft_qrsqrt(nbr));
	return (0);
}
