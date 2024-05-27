/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/05/27 18:57:24 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

//                                           ^ ^
//  1.41, not quite perfect but good enough  0_0

bool	tap_top(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	cyl->top = minus(cyl->center, mult_vecdub(cyl->vector, cyl->height_half / 2));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->top;
	tmppl.vector = cyl->vector;
	if (intersect_cyl_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		double distance = vec_length(cyl->top, obj->hit_pos);

		if (distance <= cyl->radius / 1.41)
			return (true);
	}
	return (false);
}

bool	boop_bottom(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	cyl->base = minus(cyl->center, mult_vecdub(cyl->vector, -(cyl->height_half / 2)));

	t_objs	tmppl;

	ft_bzero(&tmppl, sizeof(t_objs));
	tmppl.center = cyl->base;
	tmppl.vector = cyl->vector;
	if (intersect_cyl_plane(ray, &tmppl, obj) == true)
	{
		obj->hit_pos = plus(ray->place, mult_vecdub(ray->vector, obj->t));
		double distance = vec_length(cyl->base, obj->hit_pos);

		if (distance <= cyl->radius / 1.41)
			return (true);
	}
	return (false);
}

// hit cylinder body check
// ray->vector * t + ray->place - cyl->center
bool	cut_ends_hit_bod(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->to_center = plus(minus(ray->place, cyl->center), mult_vecdub(ray->vector, obj->t));
	if (fabs(dot_product(obj->to_center, cyl->vector)) <= cyl->height_half)
			return (true);
	return (false);
}

void	set_points(t_hit_data *obj, t_ray *ray, t_objs *cyl)
{
	t_vec3	vector_cross;
	t_vec3	oc;

	vector_cross = cross_product(cyl->vector, ray->vector);
	oc = minus(cyl->center, ray->place);
	oc = cross_product(oc, cyl->vector);
	obj->a = dot_product(vector_cross, vector_cross);
	obj->b = 2.0 * dot_product(vector_cross, oc);
	obj->c = dot_product(oc, oc) - pow(cyl->radius, 2);
}

void	cyl_normal(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	obj->hit_pos = mult_vecdub(ray->vector, obj->t);
	obj->to_center = minus(obj->hit_pos, cyl->center);
	obj->pnt = plus(cyl->center, mult_vecdub(cyl->vector, dot_product(obj->to_center, cyl->vector)));
	cyl->normal = normalize_vector(obj->pnt);
}

bool	bodyody(t_hit_data *obj, t_objs *cyl, t_ray *ray)
{
	set_points(obj, ray, cyl);
	if (quadratic(obj) == true)
	{
		if (cut_ends_hit_bod( obj, cyl, ray) == true)
		{
			// cyl->normal = normalize_vector(minus(obj->hit_pos, cyl->center));
			return (true);
		}
	}
	return (false);
}

// check this, think im seeing both caps when i should just see one and body untouched
bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_hit_data *obj)
{
	// if bottoms function, check which blah blah, then also check against body right?
	double	tmp;
	
	tmp = DBL_MAX;
	if (tap_top(obj, cyl, ray) == true)
	{
		if (obj->t < tmp)
			tmp = obj->t;
	}
	if (boop_bottom(obj, cyl, ray) == true)
	{
		if (obj->t < tmp)
			tmp = obj->t;
	}
	if (tmp != DBL_MAX)
	{
		if (tmp < obj->closest_t)
			obj->closest_t = tmp;
		return (true);
	}
	else if (bodyody(obj, cyl, ray) == true)
	{
		return (check_closest(obj));
	}
	return (false);
}
