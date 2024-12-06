/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 04:25:10 by souaguen          #+#    #+#             */
/*   Updated: 2024/11/07 22:57:12 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"


int	ft_has_intersection(t_list *shapes, t_ray *ray, void *exclude);

int     ft_get_rgb(int r, int g, int b)
{
        return (((r << 8) + g) << 8) + b;
}

void	ft_pixel_put(char **data_addr, int x, int y, int s_line, int bpp, int pixel)
{
	*(unsigned int *)((*data_addr) + (s_line * y) + (x * (bpp / 8))) = pixel;
}

t_vec3	ft_vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_list	*ft_lst_shapes()
{
	t_list	*lst_shapes;
	t_list	*tmp;
	t_shape	*shape;	
	double	size[2];
	
	size[0] = 21.2;
	size[1] = 7.1;
	lst_shapes = NULL;

	shape = ft_create_sphere(ft_vec3(40, -20, 40), 10, ft_vec3(255, 0, 0));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	//cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255

	shape = ft_create_cylinder(ft_vec3(-20, -3.55, 41.6), ft_normalize(ft_vec3(-1, 0, 0)), size, ft_vec3(10, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	/*shape = ft_create_sphere(ft_vec3(5, -4, 25), 2, ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);	

	shape = ft_create_sphere(ft_vec3(-5, 4, 25), 2, ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(5, 4, 25), 2, ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(-5, 4, 15), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(5, 4, 15), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(-5, -4, 15), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(5, -4, 15), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(-5, -4, 5), 2, ft_vec3(255, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(5, -4, 5), 2, ft_vec3(255, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	shape = ft_create_sphere(ft_vec3(-5, 4, 5), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(5, 4, 5), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	shape = ft_create_sphere(ft_vec3(-5, 4, 0), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(5, 4, 0), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(-5, -4, 0), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(5, -4, 0), 2, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_cylinder(ft_vec3(5, 3, 25), ft_vec3(0, -1, 0), size, ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	shape = ft_create_cylinder(ft_vec3(-5, 3, 25), ft_vec3(0, -1, 0), size, ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	shape = ft_create_cylinder(ft_vec3(5, 3, 15), ft_vec3(0, -1, 0), size, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	shape = ft_create_cylinder(ft_vec3(-5, 3, 15), ft_vec3(0, -1, 0), size, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_cylinder(ft_vec3(5, 3, 5), ft_vec3(0, -1, 0), size, ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_cylinder(ft_vec3(-5, 3, 5), ft_vec3(0, -1, 0), size, ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	shape = ft_create_cylinder(ft_vec3(5, 3, 0), ft_vec3(0, -1, 0), size, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_cylinder(ft_vec3(-5, 3, 0), ft_vec3(0, -1, 0), size, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_plane(ft_vec3(0, -1, 0), ft_vec3(0, 3, 20), ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
*/
/*	size[1] = 50;
	shape = ft_create_cylinder(ft_vec3(0, 2, 10), ft_vec3(0, 1, 0), size, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);*/

/*	shape = ft_create_plane(ft_vec3(0, 1, 0), ft_vec3(0, -3, -1), ft_vec3(0, 0, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
*/
/*	shape = ft_create_cylinder(ft_vec3(-5, 3, 10), ft_normalize(ft_vec3(1, -1, -1)), size, ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	*/

	shape = ft_create_plane(ft_vec3(0, -1, 0), ft_vec3(0, 3, 0), ft_vec3(255, 255, 255));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
/*	shape = ft_create_plane(ft_vec3(1, 0, 0), ft_vec3(-10, 0, -1), ft_vec3(255, 255, 0));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_plane(ft_vec3(-1, 0, 0), ft_vec3(10, 0, -1), ft_vec3(255, 255, 0));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_plane(ft_vec3(0, 0, -1), ft_vec3(0, 1, 30), ft_vec3(255, 0, 0));
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
*/
	return (lst_shapes);
}

t_vec3	ft_product(t_vec3 a, double n)
{
	a.x *= n;
	a.y *= n;
	a.z *= n;
	return (a);
}

t_vec3	ft_sum(t_vec3 a, t_vec3 b);

float	ft_qrsqrt(float nbr)
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
	return (fabs(y));
}

t_vec3	ft_normalize(t_vec3 v)
{
	float	nbr;

	nbr = fabs(ft_dot(v, v));
	//printf("%f %f\n", 1 / sqrt(nbr), ft_qrsqrt(nbr));
	return (ft_product(v, ft_qrsqrt(nbr)));
}

int	ft_is_shadow(t_ray ray, t_vec3 light, t_list *shapes)
{
	t_vec3	hit;
	t_ray	shadow;
	double	light_d;
	
	hit = ft_sum(ray.from, ft_product(ray.direction, ray.hit.distance));
	shadow.direction = ft_normalize(ft_sub(light, hit));
	shadow.from = hit;
	light = ft_sub(light, hit);
	light_d = 1 / ft_qrsqrt(ft_dot(light, light));
	if (ft_has_intersection(shapes, &shadow, ray.hit.shape_addr)
			&& light_d > shadow.hit.distance)
		return (1);
	return (0);
}

int	ft_light(t_ray *ray, t_list *shapes)
{
	t_hitpoint	hit;
	t_vec3		v;
	t_vec3		lm;
	t_vec3		n;
	double		intensity;
	double		intensity2;
	t_vec3		specular;
	int		pixel;
	t_vec3		light;
	t_vec3		color;
	t_shape		shape;

	light = ft_vec3(0, 2, 0);
	v = ft_sum((*ray).from, ft_product((*ray).direction, (*ray).hit.distance));
	hit = (*ray).hit;
	lm = ft_normalize(ft_sub(ft_sub(light, (*ray).from), v));
	n = hit.normal;
	intensity = ft_dot(lm, n);
	if (intensity < 0 || ft_is_shadow(*ray, light, shapes))
		intensity = 0;
	specular = ft_vec3(0, 0, 0);
	if (intensity > 0.001f)
		specular = ft_sub(ft_product(n, 2 * intensity), lm);
	intensity = (intensity * 1) + pow(ft_dot(specular, ft_normalize((*ray).direction)), 10) * 0 + 0;
	if (intensity > 1)
		intensity = 1;	
/*	light = ft_vec3(0, 2, 0);
	lm = ft_normalize(ft_sub(ft_sub(light, (*ray).from), v));
	n = hit.normal;
	intensity2 = ft_dot(lm, n);	
	specular = ft_vec3(0, 0, 0);
	if (intensity2 > 0.001f)
		specular = ft_sub(ft_product(n, 2 * intensity2), lm);
	if (intensity2 < 0 || ft_is_shadow(*ray, light, shapes))
		intensity2 = 0;	
	intensity2 = (intensity2 * 0.7) + pow(ft_dot(specular, ft_normalize((*ray).direction)), 10) * 0.3;
	intensity = (intensity + intensity2) / 2;
	*/
	color = ft_product((*ray).hit.pixel, intensity);
	pixel = ft_get_rgb(color.x, color.y, color.z);
	return (pixel);
}

int	ft_has_intersection(t_list *shapes, t_ray *ray, void *exclude)
{
	t_list	*cursor;
	t_list	*tmp;
	t_shape	*content;
	t_hitpoint	hit;

	hit.distance = 10000;
	cursor = shapes;
	while (cursor != NULL)
	{
		content = (*cursor).content;
		if ((*content).object != exclude 
			&& (*content).hasInter((*content).object, ray)
			&& (*ray).hit.distance > 0)
		{
			if ( (*ray).hit.distance < hit.distance)
			{
				hit = (*ray).hit;
				hit.pixel = (*content).color;
			}	
		}
		cursor = (*cursor).next;
	}
	(*ray).hit = hit;
	if (hit.distance < 10000 && hit.distance > 0)
		return (1);
	return (0);
}

void	ft_init_ray(t_ray *ray, t_vec3 dir)
{
	(*ray).hasHit = 0;
	(*ray).from = ft_vec3(0, 0, 0);	
	(*ray).hit.pixel = ft_vec3(0, 0, 0);
	(*ray).hit.distance = 0;
	(*ray).hit.shape_addr = NULL;
	(*ray).direction = dir;
}

double	ft_radian(double angle)
{
	return (angle * M_PI/180.0f);
}

void    ft_lookAt(t_vec3 matrix[3], t_vec3 forward)
{
        t_vec3  randup;
        t_vec3  right;
        t_vec3  up;
        t_vec3  transform;
        t_vec3  position;

	forward = ft_normalize(forward);
        randup = ft_vec3(0, 1, 0);
        right = ft_normalize(ft_cross_product(randup, forward));
        up = ft_normalize(ft_cross_product(forward, right));

        //position = ft_vec3(1, 1, 1);

        //transform = ft_vec3(ft_dot(position, right), ft_dot(position, up), ft_dot(position, forward));
	
        matrix[0] = right;
        matrix[1] = up;
	matrix[2] = forward;
	
}

int	main(int argc, char **argv)
{	
	t_list	*lst_shapes;
	t_ray	ray;
	t_vec3	v;
	int		i;
	int		j;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*data_addr;
	int	bpp;
	int	size_line;
	int	endian;
	int	pos[2];
	int	pixel;
	int	width;
	int	height;
	double	aspect_ratio;
	double	fov = 70.0f;
	t_vec3	matrix[3];

	i = 0;
	j = 0;
	width = 1200;
	height = 600;
	aspect_ratio = width / height;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, height, "MiniRT");
	img_ptr = mlx_new_image(mlx_ptr, width, height);
	data_addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	lst_shapes = ft_lst_shapes();
	ft_lookAt(matrix, ft_vec3(0, 0, 1));
	while (j <= height)
	{
		pixel = 0;
		v = ft_vec3(aspect_ratio * ((((double)i - 0.5)/width) * 2 - 1) * tan(ft_radian(fov / 2)), (((double)j - 0.5)/height * 2 - 1) * tan(ft_radian(fov / 2)), 1);
		
		//printf("%f\n", ft_dot(v, matrix[2]));
		v = ft_vec3(ft_dot(v, matrix[0]), ft_dot(v, matrix[1]), ft_dot(v, matrix[2]));
		v = ft_normalize(v);
		ft_init_ray(&ray, v);
		if (ft_has_intersection(lst_shapes, &ray, NULL))
			pixel = ft_light(&ray, lst_shapes);
		ft_pixel_put(&data_addr, i, j, size_line, bpp, pixel);
		if (i == width)
		{
			i = -1;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}
