/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 04:05:54 by souaguen          #+#    #+#             */
/*   Updated: 2024/11/06 04:50:43 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "mlx.h"
#include "libft.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_cam
{
	t_vec3	origin;
	t_vec3	direction;
	double	aspect_ratio;
	int	fov;
}	t_cam;

typedef struct s_hitpoint
{	
	t_vec3	direction;
	t_vec3	normal;
	double	distance;
	t_vec3	pixel;
	void	*shape_addr;
}	t_hitpoint;

typedef struct s_ray
{
	int		hasHit;
	t_hitpoint	hit;
	t_vec3		from;
	t_vec3		direction;
}	t_ray;

typedef struct s_shape
{
	void	*object;
	t_vec3	color;
	int	(*hasInter)(void *, t_ray *);
}	t_shape;

typedef struct s_cylinder
{
	t_vec3	axis;
	t_vec3	origin;
	double	height;	
	double	radius;
}	t_cylinder;

typedef struct s_sphere
{
	t_vec3	origin;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	direction;
	t_vec3	point;
}	t_plane;

float	ft_qrsqrt(float nbr);
t_sphere	ft_sphere(t_vec3 origin, double radius);
t_plane		ft_plane(t_vec3 direction, t_vec3 point);
t_cylinder	ft_cylinder(t_vec3 origin, t_vec3 axis, double height, double radius);
t_shape		*ft_create_sphere(t_vec3 origin, double radius, t_vec3 color);
t_shape		*ft_create_cylinder(t_vec3 base, t_vec3 axis, double size[2], t_vec3 color);
t_shape		*ft_create_plane(t_vec3 axis, t_vec3 point, t_vec3 color);
t_vec3		ft_sub(t_vec3 a, t_vec3 b);
t_vec3		ft_product(t_vec3 a, double n);
t_vec3		ft_normalize(t_vec3 v);
t_vec3		ft_cross_product(t_vec3 a, t_vec3 b);
void	ft_sphere_shape(t_shape **shape);
void	ft_cylinder_shape(t_shape **shape);
void	ft_plane_shape(t_shape **shape);
void	ft_shapes_alloc(void **object, t_shape **shape, unsigned int obj_size);
void	ft_shape_init(t_shape **shape, void *obj, t_vec3 color, void (f)(t_shape **));
double	ft_dot(t_vec3 a, t_vec3 b);
