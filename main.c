/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:16:43 by  souaguen         #+#    #+#             */
/*   Updated: 2024/09/28 12:39:14 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere	ft_sphere(t_vec3 origin, double radius)
{
	t_sphere	s;

	s.o = origin;
	s.r = radius;
	return (s);
}

int     get_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
        int     c;

        c = 0;
        c += red;
        c = c << 8;
        c += green;
        c = c << 8;
        c += blue;
        return (c);
}

t_vec3	ft_product(t_vec3 v, double n)
{
	v.x = v.x * n;
	v.y = v.y * n;
	v.z = v.z * n;
	return (v);
}

t_vec3	ft_sum(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

void    img_pixel_put(char **img, int size_line, int x, int y, int color)
{
        char    *data_addr;
        int             i;
	
        data_addr = *img;
        i = (y * size_line) + (x * 4);
        *(unsigned int *)(data_addr + i) = color;
}

double	get_radian(int angle)
{
	return (double)angle * (M_PI / 180);
}

int	ft_plane_intersection(t_plane pl, t_cam cam, t_vec3 *v, double *t_ptr)
{
	double	t;
	t_vec3	e;
	t_vec3 pToE;

	pToE = ft_sub(cam.e, pl.p);
	t = ft_dot(pl.n, cam.d);
	if ((int)t == 0)
		return (0);
	t = (ft_dot(pl.n, pl.p) - ft_dot(pl.n, pToE)) / t;
	if (t < 0)
		return (0);
	*v = ft_sub(ft_vec3(cam.e.x + (t * cam.d.x),
			cam.e.y + (t * cam.d.y),
			cam.e.z + (t * cam.d.z)), cam.e);
	*t_ptr = t;
	return (1);
}

int	ft_sphere_intersection(t_sphere s, t_cam cam, t_vec3 *v, double *t_ptr)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	double	t;
	double	t0;

	cam.e = ft_sub(cam.e, s.o);
	a = ft_dot(cam.d, cam.d);
	b = 2 * ft_dot(cam.e, cam.d);
	c = ft_dot(cam.e, cam.e) - pow(s.r, 2);
	dis = (pow(b, 2) - (4 * (a * c)));
	if (dis < 0)
		return (0);
	t0 = (-b + sqrt(dis)) / (2 * a);
	t = (-b - sqrt(dis)) / (2 * a);
	*t_ptr = t;
	if (v != NULL)
		*v = ft_vec3(cam.e.x + (cam.d.x * t),
				cam.e.y + (cam.d.y * t),
				cam.e.z + (cam.d.z * t));	
	return (1);
}

int	ft_get_pixel(t_cam cam, t_vec3 hit, t_vec3 light)
{
	double	diffuse;
	double	specular;
	double	n;
	t_cam	c;
	t_vec3	v;
	t_vec3	r;
	t_sphere	s;

	specular = 0;
	//c.e = hit;
	//c.d = light;
	//if (sphere != NULL)
	//{
	//	s = *sphere;
	//	s.o = ft_sub(hit, s.o);
	//	printf("%f %f %f\n", hit.x, hit.y, hit.z);
	//}

	//if (sphere != NULL && ft_sphere_intersection(s, c, NULL))
	//	return (get_rgb(255, 0, 0));
	//else if (sphere != NULL)
	//	return (get_rgb(255, 255, 255));
	//return (get_rgb(255, 255, 255));
	//return (get_rgb(255, 0, 0));
	hit = ft_normalize(hit);
	//return (get_rgb(255 * hit.z, 255 * hit.z, 255 * hit.z));
	light = ft_normalize(light);
	diffuse = ft_dot(hit, light);
	if (diffuse < 0)
		diffuse = 0;
	n = 2 * ft_dot(hit, light);
	v = ft_vec3(hit.x * n, hit.y * n, hit.z * n);
	r = ft_sub(v, light);
	if (n > 0)
		specular = pow(ft_dot(r, cam.d), 10);
	n = diffuse * 0.7 + specular * 0 + 0.2;
	if (n > 1)
		n = 1;
	return (get_rgb(0xff * n, 0xff * n, 0xff * n));
}

t_vec3	ft_prod(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;	
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

t_vec3	ft_div(t_vec3 v, double n)
{
	v.x /= n;
	v.y /= n;
	v.z /= n;
	return (v);
}

double	ft_max_vec3(t_vec3 v)
{
	double	max;
	
	max = abs(v.x);
	if (abs(v.y) > max)
		max = abs(v.y);
	if (abs(v.z) > max)
		max = abs(v.z);
	return (max);
}

int	main(int argc, char **argv)
{
	t_sphere	sphere;
	t_plane		plane;
	t_vec3		light;
	t_vec3		hit;
	t_cam		camera;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img;
	int			bpp;
	int			size_line;
	int			endian;
	int			pixel;
	double			i;
	double			j;
	t_vec3			p[4];
	int			angle;
	t_cam	c;
	double			t;
	double			tmp;

	angle = 0;
	p[0] = ft_vec3(-1, 1, -1);
	p[1] = ft_vec3(-1, 1, 1);
	p[2] = ft_vec3(1, 1, 1);
	p[3] = ft_vec3(1, 1, -1);
	t_vec3	x = ft_sub(p[3], p[0]);
	t_vec3	y = ft_sub(p[1], p[0]);
	t_vec3	n = ft_cross_product(x, y);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "MiniRT");
	img_ptr = mlx_new_image(mlx_ptr, 600, 600);
	img = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	camera.e = ft_vec3(0, 0, 0);
	sphere = ft_sphere(ft_vec3(0, 1, -6), 0.5);
	plane.n = ft_product(n, 1);
	plane.p = p[0];
	light = ft_vec3(0, 1, -5);
	t_sphere	back = sphere;
	t_sphere	s;
	while (1)
	{
		i = 0;
		//sphere.o.x = back.o.x;
		//sphere.o.y = back.o.y * cos(get_radian(angle)) + (back.o.z - (back.o.z - 2)) * -sin(get_radian(angle));
		//sphere.o.z = back.o.y * sin(get_radian(angle)) + (back.o.z - (back.o.z - 2)) * cos(get_radian(angle));
		sphere.o.x = back.o.x * cos(get_radian(angle)) + (back.o.z - (back.o.z - 2)) * sin(get_radian(angle));
		sphere.o.y = back.o.y;
		sphere.o.z = back.o.x * -sin(get_radian(angle)) + (back.o.z - (back.o.z - 2)) * cos(get_radian(angle));	
		sphere.o.x += back.o.x;	
		sphere.o.y += back.o.y;
		sphere.o.z += back.o.z;
		while (i <= 600)
		{
			j = 0;
			while (j <= 600)
			{
				pixel = 0;
				camera.d = ft_vec3((((double)j/600) * 2.0 - 1.0),
						(((double)i/600) * 2.0 - 1.0), -1);
				if (ft_sphere_intersection(sphere, camera, &hit, &t)
						&& ft_plane_intersection(plane, camera, &plane.hit, &tmp))
				{
					if (t < tmp)
						pixel = ft_get_pixel(camera, hit, ft_sub(light, sphere.o));
					else
					{
						pixel = ft_get_pixel(camera, plane.n, ft_sub(light, plane.hit));
						c.e = plane.hit;
						c.d = ft_normalize(ft_sub(light, plane.hit));
						s = sphere;
						s.o = sphere.o;
						if (ft_sphere_intersection(s, c, &hit, &tmp) && tmp > 0)
							pixel = get_rgb(0xff * 0.1, 0xff * 0.1, 0xff * 0.1);
					}
				}
				else
				{
					if (ft_plane_intersection(plane, camera, &plane.hit, &tmp))
					{
						pixel = ft_get_pixel(camera, plane.n, ft_sub(light, plane.hit));
						c.e = plane.hit;
						c.d = ft_normalize(ft_sub(light, plane.hit));
						s = sphere;
						s.o = sphere.o;
						if (ft_sphere_intersection(s, c, &hit, &tmp) && tmp > 0)
							pixel = get_rgb(0xff * 0.1, 0xff * 0.1, 0xff * 0.1);
					}
					if (ft_sphere_intersection(sphere, camera, &hit, &tmp))
						pixel = ft_get_pixel(camera, hit, ft_sub(light, sphere.o));
				}
				//printf("%f %f %f\n", hit.x, hit.y, hit.z);
				img_pixel_put(&img, size_line, j, i, pixel);
				j += 1.0;
			}
			i += 1.0;
		}
		mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
		//usleep(2000);
		angle += 1;
	}
	mlx_loop(mlx_ptr);
	return (0);
}

/*int		main(int argc, char **argv)
{
	t_sphere	sphere;
	t_vec3		e;
	t_vec3		d;
	char	*img;
	int	bpp;
	int	size_line;
	int	endian;
	double	i;
	double	j;
	t_vec3	*r;

	r = malloc(sizeof(t_vec3));
	(void)argc;
	(void)argv;
	
	printf("%f\n", M_PI / 180);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "MiniRT");
	img_ptr = mlx_new_image(mlx_ptr, 600, 600);
	img = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	sphere = ft_sphere(ft_vec3(0, 0, -10), 5);
	e = ft_vec3(0, 0, 2);
	int angle = 0;
	t_sphere	back = sphere;
	while (1)
	{
		//sphere.o.x = back.o.x;
		//sphere.o.y = back.o.y * cos(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * -sin(get_radian(angle));
		sphere.o.z = back.o.y * sin(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * cos(get_radian(angle));
		sphere.o.x = back.o.x * cos(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * sin(get_radian(angle));
		sphere.o.y = back.o.y;
		//sphere.o.z = back.o.x * -sin(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * cos(get_radian(angle));	
		sphere.o.z += back.o.z;
		i = 0;
		while (i <= 600)
		{
			j = 0;
			while (j <= 600)
			{
				d = ft_vec3(((double)j / 600) * 2.0 - 1.0, ((double)i / 600) * 2.0 - 1.0, -1);
				img_pixel_put(&img, size_line, j, i, ft_get_pixel(sphere, e, d));
				j += 1.0;
			}
			i += 1.0;
		}
		mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
		usleep(20000);
		angle = (angle + 1) % 360;
	}
	//printf("%d %d %d\n", bpp, size_line, endian);
	//ft_draw_sphere();
	mlx_loop(mlx_ptr);
	(void)mlx_ptr;
	(void)win_ptr;
	(void)img;
	return (0);
}*/
