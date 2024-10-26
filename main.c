/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 04:25:10 by souaguen          #+#    #+#             */
/*   Updated: 2024/10/26 14:47:49 by souaguen         ###   ########.fr       */
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
	
	size[0] = 4;
	size[1] = 2;
	lst_shapes = NULL;
	
	shape = ft_create_sphere(ft_vec3(-10, 0, 15), 3, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_sphere(ft_vec3(10, 0, 15), 3, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);

	shape = ft_create_cylinder(ft_vec3(5, 3, 30), ft_vec3(0, -1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_cylinder(ft_vec3(-5, 3, 30), ft_vec3(0, -1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	shape = ft_create_cylinder(ft_vec3(5, 4, 20), ft_vec3(0, -1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_cylinder(ft_vec3(-5, 4, 20), ft_vec3(0, -1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	
	shape = ft_create_cylinder(ft_vec3(5, 6, 10), ft_vec3(0, -1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_cylinder(ft_vec3(-5, 6, 10), ft_vec3(0, -1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	
	/*size[1] = 50;
	shape = ft_create_cylinder(ft_vec3(0, 2, 10), ft_vec3(0, 1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);*/
	shape = ft_create_plane(ft_vec3(0, -1, 0), ft_vec3(0, 3, 20), 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_plane(ft_vec3(0, 1, 0), ft_vec3(0, -3, -1), 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_plane(ft_vec3(1, 0, 0), ft_vec3(-10, 0, -1), 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_plane(ft_vec3(-1, 0, 0), ft_vec3(10, 0, -1), 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_plane(ft_vec3(0, 0, -1), ft_vec3(0, 1, 30), 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
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

t_vec3	ft_normalize(t_vec3 v)
{
	return (ft_product(v, 1 / sqrt(ft_dot(v, v))));
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
	light_d = sqrt(ft_dot(light, light));
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
	int		pixel;
	t_vec3		light;

	light = ft_vec3(0, -2, 15);
	v = ft_sum((*ray).from, ft_product((*ray).direction, (*ray).hit.distance));
	hit = (*ray).hit;
	lm = ft_normalize(ft_sub(ft_sub(light, (*ray).from), v));
	n = hit.normal;
	intensity = ft_dot(lm, n);
	if (intensity < 0 || ft_is_shadow(*ray, light, shapes))
		intensity = 0;
	intensity = (intensity * 1) + 0;
	pixel = ft_get_rgb(255 * intensity, 255 * intensity, 255 * intensity);
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
				hit = (*ray).hit;
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
	(*ray).hit.distance = 0;
	(*ray).hit.shape_addr = NULL;
	(*ray).direction = dir;
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

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "MiniRT");
	img_ptr = mlx_new_image(mlx_ptr, 600, 600);
	data_addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	i = 0;
	j = 0;
	lst_shapes = ft_lst_shapes();
	while (j <= 600)
	{
		pixel = 0;
		v = ft_vec3(((double)i/600) * 2 - 1, ((double)j/600) * 2 - 1, 1);
		ft_init_ray(&ray, v);
		if (ft_has_intersection(lst_shapes, &ray, NULL))
			pixel = ft_light(&ray, lst_shapes);
		ft_pixel_put(&data_addr, i, j, size_line, bpp, pixel);
		if (i == 600)
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
