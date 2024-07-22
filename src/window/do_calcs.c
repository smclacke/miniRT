/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   do_calcs.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/16 16:14:41 by smclacke      #+#    #+#                 */
/*   Updated: 2024/07/22 17:56:06 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

// L             -10,0,-4    0.6   0,200,255
// L             10,0,-4    0.6   0,200,255

// sp                 -3,0,-25        4          0,0,255
// sp                 -1,0,-30        4          255,0,0
// sp                  -5,0,-20        4           0,255,0

// WITH THIS CODE: 
// mult + plus
// two lights, 10 + -10 no shadow = good
// one light -10, shadow on red but not blue = bad
// one light 10, shadow on green (looks like the blue sphere shadowed on top) = bad

// WITH:
// div seems to give no shadows at all..
// div + plus
// one light 10, no shadow = good
// one light -10, no shadow = bad
// two lights, 10 + -10 no shadow = good

// WITHOUT OBJ WHILE + MULT + PLUS
// one -10, good shadows
// one 10 totally fucked
// two lights, loads of light and fucked shadow on blue = bad

// WITHOUT OBJ WHILE + DIV + PLUS
// two lights, no shadow = good
// one -10 no shaodw = bad
// one 10 

// CONCLUSION: div no shadow, obj while no real difference, fix it with mult and plus

// div seems to give no shadows at all..
// inter_p = division_vec_dub(data->pix[i]->og_ray.vector, data->pix[i]->hit_t);
// sometimes mult/div, sometimes minus/plus (i think no more minus tho)

static bool	check_all_after(t_data *data, int i)
{
	int	light_i;
	int	obj_i;

	light_i = 0;
	obj_i = 0;
	while (light_i < data->light_i)
	{
		obj_i = 0;
		while (obj_i < data->objs_i)
		{
			if (data->objs[obj_i]->in_light == true)
				return (true);
			obj_i++;
		}
		if (data->light[light_i]->in_light == true)
			return (true);
		light_i++;
	}
	if (data->pix[i]->in_light == true)
		return (true);
	return (false);
}

static bool	in_light(t_data *data, int i)
{
	int				light_i = 0;
    t_hit_data		hit_2;
	t_ray			ray;
	int				obj_i = 0;

	data->pix[i]->in_light = true;
	data->objs[obj_i]->in_light = true;
	while (light_i < data->light_i)
	{
		data->light[light_i]->in_light = true;
		obj_i = 0;
		ft_bzero(&ray, sizeof(t_ray));
		ray = init_light_ray(data, i, light_i);
		while (obj_i < data->objs_i)
		{
			ft_bzero(&hit_2, sizeof(t_hit_data));
			if (does_intersect(&ray, data->objs[obj_i], &hit_2)
				&& data->objs[obj_i] != data->pix[i]->obj)
				{
					data->light[light_i]->in_light = false;
					data->objs[obj_i]->in_light = false;
					data->pix[i]->in_light = false;
					break ;
				}
			obj_i++;
		}
		light_i++;
	}
	if (check_all_after(data, i) == true)
		return (true);
	return (false);
}

static void	initial_cals(t_data *data)
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
}

void	do_calcs(t_data *data)
{
	initial_cals(data);
	data->i = 0;
	while (data->i < data->total_pix)
	{
		if (data->pix[data->i]->hit_b == true)
		{
			if (in_light(data, data->i))
				data->pix[data->i]->colour = data->pix[data->i]->light;
			else
				data->pix[data->i]->colour = data->pix[data->i]->ambient;
		}
		data->i++;
	}
}
