/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:16:43 by  souaguen         #+#    #+#             */
/*   Updated: 2024/09/19 07:24:05 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>

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

double		ft_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3		ft_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x - b.x;
	v.y = a.y - b.y;
	v.z = a.z - b.z;
	return (v);
}



t_vec3		ft_sum(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x + b.x;
	v.y = a.y + b.y;
	v.z = a.z + b.z;
	return (v);
}

t_vec3		ft_prod(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = a.x * b.x;
	v.y = a.y * b.y;
	v.z = a.z * b.z;
	return (v);
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

t_vec3	ft_normalize(t_vec3 r)
{
	t_vec3	v;
	double	length;
	
	length = sqrt(ft_dot(r, r));
	v.x = r.x / length;
	v.y = r.y / length;
	v.z = r.z / length;
	return (v);
}

int	ft_get_pixel(t_sphere s, t_vec3 e, t_vec3 d)
{
	double	a;
	double	b;
	double	c;
	double	dis;
	t_vec3	t;
	t_vec3	ray;
	t_vec3	light;
	
	light = ft_vec3(0, -10, -4);//I

	// Hitting sphere Equation:
	//
	// (d.x^2 + d.y^2 + d.z^2) * t^2 + (2 * (e.x * d.x) + 2 * (e.y * d.y) + 2 * (e.z * d.z)) * t + (d.x^2 + d.y^2 + d.z^2 - s.r^2) = 0
	// a = (d.x^2 + d.y^2 + d.z^2)
	// b = (2 * (e.x * d.x) + 2 * (e.y * d.y) + 2 * (e.z * d.z))
	// c = (d.x^2 + d.y^2 + d.z^2 - s.r^2)
	//
	// (b^2 - 4ac) > 0
	e.y = e.y;
	e = ft_sub(e, s.o);
	a = ft_dot(d, d);
	b = 2 * ft_dot(e, d);
	c = ft_dot(e, e) - pow(s.r, 2);
	
	dis = (pow(b, 2) - (4 * (a * c)));
	if (dis < 0)
		return (0);
	t.x = (-b + sqrt(dis)) / (2 * a);
	t.y = (-b - sqrt(dis)) / (2 * a);
	if (t.x < t.y)
		ray = ft_vec3(e.x + (d.x * t.x), e.y + (d.y * t.x), e.z + (d.z * t.x));
	else
		ray = ft_vec3(e.x + (d.x * t.y), e.y + (d.y * t.y), e.z + (d.z * t.y));
	double	length = sqrt(ft_dot(ray, ray));
	ray.x = ray.x / length;
	ray.y = ray.y / length;
	ray.z = ray.z / length; // N
	double intensity = ft_dot(ray, light) * 0.5; 
	//	double	intensity = (sqrt(pow(ray.x, 2)) + sqrt(pow(ray.y, 2) + sqrt(pow(ray.z, 2)))) / 3;
	if (intensity < 0)
	{
		return (get_rgb(0, 0, 0));
	}

	//printf("%f\n", intensity);
	if (intensity > 1)
		intensity = 1;
	return (get_rgb(255 * intensity, 255 * intensity, 255 * intensity));	
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

int		main(int argc, char **argv)
{
	t_sphere	sphere;
	t_vec3		e;
	t_vec3		d;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
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
	sphere = ft_sphere(ft_vec3(0, 0, -10), 4);
	e = ft_vec3(0, 0, 2);
	int angle = 0;
	t_sphere	back = sphere;
	while (1)
	{
	//	sphere.o.x = back.o.x;
	//	sphere.o.y = back.o.y * cos(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * -sin(get_radian(angle));
	//	sphere.o.z = back.o.y * sin(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * cos(get_radian(angle));
		sphere.o.x = back.o.x * cos(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * sin(get_radian(angle));
		sphere.o.y = back.o.y;
		sphere.o.z = back.o.x * -sin(get_radian(angle)) + (back.o.z - (back.o.z - 5)) * cos(get_radian(angle));	
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
	//mlx_loop(mlx_ptr);
	(void)mlx_ptr;
	(void)win_ptr;
	(void)img;
	return (0);
}
