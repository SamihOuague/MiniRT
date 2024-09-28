/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:02:58 by  souaguen         #+#    #+#             */
/*   Updated: 2024/09/27 17:08:42 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>

typedef struct	s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct	s_obj
{
	void	*ptr;
	char	type;	
}	t_obj;

typedef struct	s_sphere
{
	t_vec3	o;
	double	r;
	int	color;
}	t_sphere;

typedef struct	s_plane
{
	t_vec3	p;
	t_vec3	n;
	t_vec3	hit;
	int	color;
}	t_plane;

typedef struct	s_cam
{
	t_vec3	e;
	t_vec3	d;
}	t_cam;

t_sphere	ft_sphere(t_vec3 origin, double radius);
t_vec3		ft_vec3(double x, double y, double z);
t_vec3		ft_normalize(t_vec3 v);
t_vec3		ft_cross_product(t_vec3 a, t_vec3 b);
t_vec3		ft_sub(t_vec3 a, t_vec3 b);
t_vec3		ft_sum(t_vec3 a, t_vec3 b);
t_vec3		ft_prod(t_vec3 a, t_vec3 b);
double		ft_dot(t_vec3 a, t_vec3 b);
int		ft_get_rgb(unsigned char r, unsigned char g, unsigned char b);
