/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 05:44:26 by souaguen          #+#    #+#             */
/*   Updated: 2024/10/19 02:17:38 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_plane_intersection(void *plane, t_ray *ray)
{
	t_plane	pl;
	
	pl = *(t_plane *)plane;
	// Plane intersection code here :
	//
	//
	// printf("Plane intersection\n");
	return (0);
}

t_plane	ft_plane(t_vec3 direction, t_vec3 point)
{
	t_plane	plane;

	plane.direction = direction;
	plane.point = point;
	return (plane);
}

void	ft_plane_shape(t_shape **shape)
{
	if (shape == NULL || *shape == NULL)
		return ;
	(**shape).hasInter = &ft_plane_intersection;
}
