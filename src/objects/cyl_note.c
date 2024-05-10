// without hit variables

			// static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
			// {
			// 	obj->tmp_t = obj->t;
			// 	// double	hit1 = 0;
			// 	// double	hit2 = 0;
			// 	double	t1 = ray->place.y + obj->root1 * ray->vector.y;
			// 	double	t2 = ray->place.y + obj->root2 * ray->vector.y;

			// 	if (t1 < (cyl->vector.y - obj->height_half) || t1 > cyl->vector.y + obj->height_half)
			// 		obj->root1 = INFINITY;
			// 		// hit1 = obj->root1;
			// 	if (t2 < (cyl->vector.y - obj->height_half) || t2 > cyl->vector.y + obj->height_half)
			// 		obj->root2 = INFINITY;
			// 		// hit2 = obj->root2;
			// 	obj->tmp_t = fmin(obj->root1, obj->root2);
			// 	// obj->tmp_t = fmin(hit1, hit2);
			// 	if (obj->tmp_t > 0)
			// 	{
			// 		double	denom = dot_product(ray->vector, cyl->vector);
			// 		if (fabs(denom) > EPSILON)
			// 		{
			// 			t_vec3	oc = minus(ray->place, cyl->center);
			// 			obj->tmp_t = -dot_product(oc, cyl->vector) / denom;
			// 			if (obj->tmp_t >= cyl->height)
			// 			{
			// 				obj->t = obj->tmp_t;
			// 				return (check_closest(obj));
			// 			}
			// 			else
			// 				return (false);
			// 		}
			// 	}
			// 	return (false);
			// }

// old plane bit

			// if (obj_data->t > 0)
			// 			{
			// 				// printf("here\n");
			// 				// exit(EXIT_SUCCESS);
			// 				// solve_capps
			// 				double	denom = dot_product(ray->vector, cyl->vector);
			// 				if (fabs(denom) > EPSILON)
			// 				{
			// 					t_vec3	oc = minus(ray->place, cyl->center);
			// 					obj_data->t = -dot_product(oc, cyl->vector) / denom;
			// 					if (obj_data->t >= EPSILON)
			// 						return (check_closest(obj_data));
			// 				}
			// 				return (false);
			// 			}

// old version before function split

			// double	t1 = ray->place.y + obj_data->root1 * ray->vector.y;
			// double	t2 = ray->place.y + obj_data->root2 * ray->vector.y;
			// if (t1 < (cyl->vector.y - height_half) || t1 > cyl->vector.y + height_half)
			// 	obj_data->t = obj_data->root1;
			// 	// obj_data->root1 = INFINITY;
			// else if (t2 < (cyl->vector.y - height_half) || t2 > cyl->vector.y + height_half)
			// 	obj_data->t = obj_data->root2;
			// 	// obj_data->root2 = INFINITY;
			// // printf("root1 = %f | root2 = %f\n", obj_data->root1, obj_data->root2);
			// // exit(EXIT_SUCCESS);
			// // obj_data->t = fmin(obj_data->root1, obj_data->root2);
			// // printf("t = %f\n", obj_data->t);
			// // exit(EXIT_SUCCESS);
			// // if (obj_data->t == INFINITY || obj_data->t == 0)
			// // 	return (true);
			// if (obj_data->t > 0)
			// {
			// 	// printf("here\n");
			// 	// exit(EXIT_SUCCESS);
			// 	// solve_capps
			// 	double	denom = dot_product(ray->vector, cyl->vector);
			// 	if (fabs(denom) > EPSILON)
			// 	{
			// 		t_vec3	oc = minus(ray->place, cyl->center);
			// 		obj_data->t = -dot_product(oc, cyl->vector) / denom;
			// 		if (obj_data->t >= EPSILON)
			// 			return (check_closest(obj_data));
			// 	}
			// 	return (false);
			// }
			// else if (obj_data->t < 0) //- no intersection
			// 	return (false);

// possible solution ish not really

		// 	if (obj_data->t > 0)
		// 	{
		// 		// check caps (top) using height, for bottom we need base point
		// 		// return (check_closest(obj_data));
		// 		double	distance;
		// 		double	denom = dot_product(ray->vector, cyl->vector);
		// 		t_vec3	oc = minus(cyl->center, ray->place);
		// 		t_vec3	hit;
		// 		if (fabs(denom) > EPSILON)
		// 		{
		// 			distance = dot_product(oc, cyl->vector); // minus and div denom
		// 			hit = plus(mult_vecdub(ray->vector, distance), ray->place);
		// 			// if vector length (hit , height (for top ? )) <= cyl->radius
		// 			if (length_squared(hit) + sqrt(cyl->height) <= radius)
		// 			{
		// 				if (distance > 0 && distance < obj_data->t)
		// 					return (check_closest(obj_data));
		// 			}
		// 		}
		// 	}
		// }

static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
{
	obj->tmp_t = obj->t;
	obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
	obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;

	if (obj->hit1 < (cyl->vector.y - obj->height_half) || obj->hit1 > cyl->vector.y + obj->height_half)
		obj->root1 = obj->hit1;
		// obj->hit1 = obj->root1;
	if (obj->hit2 < (cyl->vector.y - obj->height_half) || obj->hit2 > cyl->vector.y + obj->height_half)
		obj->root2 = obj->hit2;
		// obj->hit2 = obj->root2;

	// obj->tmp_t = fmin(obj->hit1, obj->hit2);
	obj->tmp_t = fmin(obj->root1, obj->root2);

	if (obj->tmp_t > 0)
	{
		double	denom = dot_product(ray->vector, cyl->vector);
		t_vec3	oc = minus(cyl->center, ray->place);
		if (fabs(denom) > EPSILON)
		{
			obj->tmp_t = dot_product(oc, cyl->vector) / denom;
			if (obj->tmp_t >= obj->height_half)
				return (true);
			else
				return (false);
		}
	}
	return (false);
}

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	t_vec3	c_c;
	t_vec3	r_c;

	r_c = cross_product(cyl->vector, ray->vector);
	c_c = minus(ray->place, cyl->center);
	c_c = cross_product(c_c, cyl->vector);
	
	obj->radius = cyl->diameter / 2;
	obj->height_half = cyl->height / 2;

	obj->a = dot_product(r_c, r_c);
	obj->b = -2.0 * dot_product(r_c, c_c);
	obj->c = dot_product(c_c, c_c) - pow(obj->radius, 2);
	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{	
			if (check_caps(obj, cyl, ray) == true)
			{
				obj->t = obj->tmp_t;
				return (check_closest(obj));
			}
			else
				return (false);
				// return (check_closest(obj));	
		}
	}
	return (false);
}


//--------------------//

// static bool	check_caps(t_obj_data *obj, t_objs *cyl, t_ray *ray)
// {
// 	obj->tmp_t = obj->t;
// 	// obj->hit1 = ray->place.y + obj->root1 * ray->vector.y;
// 	// obj->hit2 = ray->place.y + obj->root2 * ray->vector.y;

// 	// if (obj->hit1 < (cyl->vector.y - obj->height_half) || obj->hit1 > cyl->vector.y + obj->height_half)
// 	// 	obj->root1 = obj->hit1;
// 	// 	// obj->hit1 = obj->root1;
// 	// if (obj->hit2 < (cyl->vector.y - obj->height_half) || obj->hit2 > cyl->vector.y + obj->height_half)
// 	// 	obj->root2 = obj->hit2;
// 		// obj->hit2 = obj->root2;

// 	// obj->tmp_t = fmin(obj->hit1, obj->hit2);
// 	obj->tmp_t = fmin(obj->root1, obj->root2);

// 	if (obj->tmp_t > 0)
// 	{
// 		double	denom = dot_product(ray->vector, cyl->vector);
// 		t_vec3	oc = minus(cyl->center, ray->place);
// 		if (fabs(denom) > EPSILON)
// 		{
// 			obj->tmp_t = dot_product(oc, cyl->vector) / denom;
// 			if (obj->tmp_t >= obj->height_half)
// 				return (true);
// 			else
// 				return (false);
// 		}
// 	}
// 	return (false);
// }

static void	check_hit(double root, t_objs *cyl, t_ray *ray, t_obj_data *obj)
{
	t_vec3	a;
	t_vec3	b;

	b = plus(cyl->center, mult_vecdub(cyl->vector, cyl->height));
	a = plus(ray->place, mult_vecdub(ray->vector, obj->t));

	if (dot_product(cyl->vector, minus(a, cyl->center)) <= 0)
		root = -1;
	if (dot_product(cyl->vector, minus(a, b)) >= 0)
		root = -1;
}	

bool	intersect_cylinder(t_ray *ray, t_objs *cyl, t_obj_data *obj)
{
	t_vec3	c_c;
	t_vec3	r_c;

	r_c = cross_product(cyl->vector, ray->vector);
	c_c = minus(ray->place, cyl->center);
	c_c = cross_product(c_c, cyl->vector);
	
	obj->radius = cyl->diameter / 2;
	obj->height_half = cyl->height / 2;

	obj->a = dot_product(r_c, r_c);
	obj->b = -2.0 * dot_product(r_c, c_c);
	obj->c = dot_product(c_c, c_c) - pow(obj->radius, 2);
	if (quadratic(obj) == true)
	{
		if (obj->t > EPSILON)
		{	
			if (obj->root1 > 0)
				check_hit(obj->root1, cyl, ray, obj);
			if (obj->root2 > 0)
				check_hit(obj->root2, cyl, ray, obj);
			if (obj->root1 < 0 && obj->root2 < 0)
				return (false);
			if ((obj->root2 < obj->root1 && obj->root2 > 0) || (obj->root1 < obj->root2 && obj->root1 <= 0)) 
				obj->t = obj->root2;
			else
				obj->t = obj->root1;
			return (true); // check_closest(obj);
		// 	if (check_caps(obj, cyl, ray) == true)
		// 	{
		// 		obj->t = obj->tmp_t;
		// 		return (check_closest(obj));
		// 	}
		// 	else
		// 		return (false);
				// return (check_closest(obj));	
		}
	}
	return (false);
}
