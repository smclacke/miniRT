/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/07 15:02:19 by smclacke      #+#    #+#                 */
/*   Updated: 2024/03/25 15:11:29 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/parser.h"

/**
 * @brief	takes array of strings from read_file()
 * 			checks the elements and values are correct
 * 			converts from string to double/int etc..
 * 			adds them to the t_data struct
 * 			if something wrong, function will free, error and exit
 * 			will not return here if error
 * @brief	(check elements + validate_elems) 
 * 			while input is in string format, check it's validity
 * 			Ambient light, Light and Camera must be declared and only once
 * 			all other elements (sp, cy, pl) must be declared, poss multi
 * 			if error/invalid, free in check function, error and exit
 * 			number of arguments and characters checked before conversion
*/
static void	parse_array(t_data *data, char **arr)
{
	int		obj_count;

	check_elements(arr);
	obj_count = validate_elems(arr);
	convert_cap_input(data, arr);
	convert_obj_input(data, arr, obj_count);
	if (data->objs->i != obj_count)
	{
		free(data->objs);
		free_arr_error("parser error", arr, NULL);
	}
}

/**
 * @brief	read through the file line by line, copying each
 * 			line into a 2D array of strings (arr)
 * 			if error occurs, array and line is freed, file is closed,
 * 			error message and exit
 * 			else close file, call parse_array which checks input, converts it
 * 			and adds everything into t_data struct, 
 * 			then frees array and line and returns to main to continue
 * 			rt_malloc is protected :)
*/
static void	read_file(t_data *data, int file)
{
	char	*line;
	char	**arr;
	int		i;

	i = 0;
	line = get_next_line(file);
	arr = rt_malloc(NULL, BUFF_SIZE, file);
	while (line)
	{
		if (line)
		{
			arr[i] = ft_strdup(line);
			if (!arr[i])
				free_close_parse_error("malloc failure", arr, line, file);
			free(line);
			line = get_next_line(file);
			i++;
		}
	}
	arr[i] = NULL;
	free_close_util(line, file);
	parse_array(data, arr);
	free_array(arr);
}

static void	check_file_type(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (is_dot(arg[i]))
		{
			if (ft_strcmp(&arg[i], ".rt") == 0)
				return ;
			else
				error_msg2("wrong file type");
		}
		i++;
	}
	error_msg2("wrong file type");
}

void	parse_input(int argc, char **argv, t_data *data)
{
	int		file;

	file = 0;
	if (argc != 2)
		error_msg2("wrong number of arguments");
	check_file_type(argv[1]);
	file = open(argv[1], O_RDONLY, 0644);
	if (file == -1)
		error_msg2("couldn't open file");
	read_file(data, file);
}
