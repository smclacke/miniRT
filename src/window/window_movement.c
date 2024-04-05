/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   window_movement.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 16:05:43 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/03 14:00:42 by jmetzger      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/miniRT.h"

void ft_key_action(mlx_key_data_t keydata, t_data *data)
{
	(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		printf("obj\n");
	
	// mouse movement, selecting objects using arrows so change if it's checkerboard or earth.
	// shift l, switches the light souses ;light source displayed over camera
}

// Handle mouse movement
// void ft_handle_mouse_move(void *data) 
// {
// 	t_data *data;
// 	i)
//     printf("Mouse moved to:\n");
// }

// // Handle mouse click
// int handle_mouse_click(int button, void *data) 
// {
// 	(void)data;
// 	if (button == MLX_MOUSE_BUTTON_LEFT)
		
//     printf("Mouse clicked at: with button %d\n", button);
//     return 0;
// }