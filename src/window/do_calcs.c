/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/22 12:13:12 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

/**
 * @todo norming... everywhere
 */
// static t_ray	init_light_ray(t_data *data, int i, int light_i)
// {
// 	t_vec3  inter_p = mult_vecdub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t);
// 	t_vec3  light_dir = minus(data->light[light_i]->place, inter_p);

// 	data->pix[i]->light_ray.place = inter_p;
// 	data->pix[i]->light_ray.vector = light_dir;
// 	return (data->pix[i]->light_ray);
// }

// // with more objects + mixed objs, might actually need a closest check, can see triangle shadow inside
// // sphere that is in front, so the order is getting messed up somehow.. (see screenshots)

// // FIND CLOSEST OBJ TO LIGHT? WHEN WHILE OBJS, IF PIX->OBJ TRI + SPHERE INFRONT, 
// // "TRI PIX" IS IN SHADOW BUT = SPHERE IS IN SHADOW AT THAT SECTION

// static bool	in_light(t_data *data, int i)
// {
//     int				obj_i = 0;
// 	int				light_i = 0;
//     t_hit_data		hit_2;
// 	t_ray			ray;
// 	bool			in_light = true;

// 	while (light_i < data->light_i)
// 	{
// 		ray = init_light_ray(data, i, light_i);
// 		while (obj_i < data->objs_i)
// 		{
// 			if (intersect_sphere(&ray, data->objs[obj_i], &hit_2)
// 				|| intersect_triangle(&ray, data->objs[obj_i], &hit_2)
// 				|| intersect_cylinder(&ray, data->objs[obj_i], &hit_2)
// 				|| intersect_plane(&ray, data->objs[obj_i], &hit_2))
// 				{
// 				if (data->objs[obj_i] != data->pix[i]->obj)
// 					in_light = false;
// 				else
// 					in_light = true;
// 				}
// 			obj_i++;
// 		}
// 		light_i++;
// 	}
// 	if (in_light == true)
// 		return (true);
// 	return (false);
// }

void	do_calcs(t_data *data)
{
	t_hit_data	hit;

	data->i = 0;
	while (data->i < data->total_pix)
	{
		data->ray = ft_create_ray(data, data->pix[data->i]->x,
				data->pix[data->i]->y);
		data->pix[data->i]->og_ray = data->ray;
		ft_calculate_colour(data, &hit, data->i);
		data->mouse.mou_y = data->pix[data->i]->y;
		data->mouse.mou_x = data->pix[data->i]->x;
		data->pix[data->i]->hit_t = hit.t;
		data->i++;
	}
	// data->i = 0;
	// while (data->i < data->total_pix)
	// {
	// 	if (data->pix[data->i]->hit_b == true)
	// 	{
	// 		if (in_light(data, data->i))
	// 			data->pix[data->i]->colour = data->pix[data->i]->light;
	// 		else
	// 			data->pix[data->i]->colour = data->pix[data->i]->ambient;
	// 	}
	// 	data->i++;
	// }
}
