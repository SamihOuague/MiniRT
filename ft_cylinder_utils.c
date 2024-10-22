/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 05:07:00 by souaguen          #+#    #+#             */
/*   Updated: 2024/10/19 02:17:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_cylinder_intersection(void *cylinder, t_ray *ray)
{
	t_cylinder	cy;

	cy = *(t_cylinder *)cylinder;
	// Intersection code
	//
	//
	//printf("Cylinder intersection\n");
	return (0);
}

t_cylinder	ft_cylinder(t_vec3 origin, t_vec3 axis, double height, double radius)
{
	t_cylinder	cy;

	cy.axis = axis;
	cy.origin = origin;
	cy.height = height;
	cy.radius = radius;
	return (cy);
}

void	ft_cylinder_shape(t_shape **shape)
{
	if (shape == NULL || *shape == NULL)
		return ;
	(**shape).hasInter = &ft_cylinder_intersection;
}
