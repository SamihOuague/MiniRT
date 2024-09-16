/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:16:43 by  souaguen         #+#    #+#             */
/*   Updated: 2024/09/16 20:15:56 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include <mlx.h>

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
	//printf("%f, %f\n", d.x, d.y);
	a = pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2);
	b = 2 * ((e.x * d.x) + (e.y * d.y) + (e.z * d.z));
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

void    img_pixel_put(char **img, int size_line, int x, int y)
{
        char    *data_addr;
        int             i;
	int		color;
	
        color = get_rgb(255, 255, 255);
        data_addr = *img;
        i = (y * size_line) + (x * 4);
        *(unsigned int *)(data_addr + i) = color;
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
	
	(void)argc;
	(void)argv;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 600, 600, "MiniRT");
	img_ptr = mlx_new_image(mlx_ptr, 600, 600);
	img = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	sphere = ft_sphere(ft_vec3(0, 0, -1), 0.5);
	e = ft_vec3(0, 0, 0);
	i = 0;
	while (i <= 600)
	{
		j = 0;
		while (j <= 600)
		{
			d = ft_vec3(((double)j / 600) * 2.0 - 1.0, ((double)i / 600) * 2.0 - 1.0, -1.0);
			if (ft_has_intersection(sphere, e, d))
				img_pixel_put(&img, size_line, j, i);
			j += 1.0;
		}
		i += 1.0;
	}
	//printf("%d %d %d\n", bpp, size_line, endian);
	//ft_draw_sphere();
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
	(void)mlx_ptr;
	(void)win_ptr;
	(void)img;
	return (0);
}
