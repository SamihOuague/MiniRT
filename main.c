/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:16:43 by  souaguen         #+#    #+#             */
/*   Updated: 2024/09/15 10:42:30 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_sphere
{
	t_vec3	o;
	double	r;
}	t_sphere;

t_vec3		ft_vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_sphere	ft_sphere(t_vec3 origin, double radius)
{
	t_sphere	s;

	s.o = origin;
	s.r = radius;
	return (s);
}

double	ft_pow(double x)
{
	double	n;

	n = x * x;
	if ((n / x) != x)
		return (-1);
	return (n);
}

int	ft_has_intersection(t_sphere s, t_vec3 e, t_vec3 d)
{
	double	a;
	double	b;
	double	c;

	e.x -= s.o.x;
	e.y -= s.o.y;
	e.z -= s.o.z;

	d.x -= s.o.x;
	d.y -= s.o.y;
	d.z -= s.o.z;
	
	a = pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2);
	b = (2 * (e.x * d.x)) + (2 * (e.y + d.y)) + (2 * (e.z + d.z));
	c = pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2) - pow(s.r, 2);

	// Hitting sphere Equation:
	//
	// (d.x^2 + d.y^2 + d.z^2) * t^2 + (2 * (e.x * d.x) + 2 * (e.y * d.y) + 2 * (e.z * d.z)) * t + (d.x^2 + d.y^2 + d.z^2 - s.r^2) = 0
	// a = (d.x^2 + d.y^2 + d.z^2)
	// b = (2 * (e.x * d.x) + 2 * (e.y * d.y) + 2 * (e.z * d.z))
	// c = (d.x^2 + d.y^2 + d.z^2 - s.r^2)
	//
	// (b^2 - 4ac) > 0
	return ((pow(b, 2) - (4 * (a * c))) > 0);
}

int		main(int argc, char **argv)
{
	t_sphere	sphere;
	t_vec3		e;
	t_vec3		d;
	(void)argc;
	(void)argv;

	sphere = ft_sphere(ft_vec3(1, 1, -5), 4.5);
	e = ft_vec3(0, 0, 0);
	int	i;
	int	j;

	i = -10;
	while (i < 10)
	{
		j = -10;
		while (j < 10)
		{
			d = ft_vec3(i - 0.5, j - 0.5, -1);
			if (ft_has_intersection(sphere, e, d))
				printf("0");
			else
				printf("1");
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}
