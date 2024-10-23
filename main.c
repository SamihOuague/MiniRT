/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 04:25:10 by souaguen          #+#    #+#             */
/*   Updated: 2024/10/23 12:04:54 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "get_next_line.h"

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
	shape = ft_create_sphere(ft_vec3(-10, 0, 20), 3, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_sphere(ft_vec3(10, 0, 20), 3, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_cylinder(ft_vec3(0, 2, 15), ft_vec3(0, 1, 0), size, 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_plane(ft_vec3(0, 1, 0), ft_vec3(0, -3, -1), 0xff00ff);
	tmp = ft_lstnew(shape);
	ft_lstadd_front(&lst_shapes, tmp);
	shape = ft_create_plane(ft_vec3(0, -1, 0), ft_vec3(0, 3, -1), 0xff00ff);
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

t_vec3	ft_normalize(t_vec3 v)
{
	return (ft_product(v, 1 / sqrt(ft_dot(v, v))));
}

int	ft_light(t_ray *ray)
{
	t_hitpoint	hit;
	t_vec3		v;
	t_vec3		lm;
	t_vec3		n;
	double		intensity;
	int		pixel;

	v = ft_product((*ray).direction, (*ray).hit.distance);
	hit = (*ray).hit;

	lm = ft_normalize(ft_sub(ft_vec3(0, 0, 9), v));
	n = hit.normal;
	intensity = ft_dot(lm, n);
	if (intensity < 0)
		intensity = 0;
	//intensity = (intensity * 0.90) + 0.1;
	pixel = ft_get_rgb(255 * intensity, 255 * intensity, 255 * intensity);
	return (pixel);
}

int	ft_has_intersection(t_list *shapes, t_ray *ray)
{
	t_list	*cursor;
	t_list	*tmp;
	t_shape	*content;
	t_hitpoint	hit;

	hit.distance = -1;
	cursor = shapes;
	while (cursor != NULL)
	{
		content = (*cursor).content;
		if ((*content).hasInter((*content).object, ray))
		{
			if (hit.distance < 0 || (*ray).hit.distance < hit.distance)
				hit = (*ray).hit;
		}
		cursor = (*cursor).next;
	}
	(*ray).hit = hit;
	if (hit.distance > 0)
		return (ft_light(ray));
	return (0);
}

void	ft_init_ray(t_ray *ray, t_vec3 dir)
{
	(*ray).hasHit = 0;
	(*ray).from = ft_vec3(0, 0, 0);
	(*ray).hit.distance = 0;
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

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "MiniRT");
	img_ptr = mlx_new_image(mlx_ptr, 600, 600);
	data_addr = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	i = 0;
	j = 0;
	lst_shapes = ft_lst_shapes();
	while (j <= 600)
	{
		v = ft_vec3(((double)i/600) * 2 - 1, ((double)j/600) * 2 - 1, 1);
		ft_init_ray(&ray, v);
		ft_pixel_put(&data_addr, i, j, size_line, bpp, ft_has_intersection(lst_shapes, &ray));
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
