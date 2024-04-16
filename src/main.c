/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 19:29:03 by smclacke      #+#    #+#                 */
/*   Updated: 2024/04/16 19:01:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../header/parser.h"
#include "../header/miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

	parse_input(argc, argv, &data);

	ft_open_window(&data); // Open window
	ft_render(&data); // the whole shazam!

	mlx_loop(data.mlx);		// loop
	//	mlx_delete_image(image);
	//	mlx_delete_texture(texture);
	mlx_terminate(data.mlx); // terminate

	free_objects(&data);	// needs to be part of the clean up
	return (EXIT_SUCCESS);
}
