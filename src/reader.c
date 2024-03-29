/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42istanbul <42istanbul.com.tr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:39:32 by 42istanbu         #+#    #+#             */
/*   Updated: 2023/02/23 18:07:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/reader.h"

char	**split(char *str)
{
	char	**matrix;
	int		index;
	int		matrix_index;
	int		matrix_second;

	index = 0;
	matrix_second = 0;
	matrix_index = 0;
	matrix = (char **)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[index])
	{
		if (str[index] == '\n')
		{
			matrix[matrix_index][index] = '\0';
			matrix_index++;
			matrix_second = 0;
		}
		matrix[matrix_index][matrix_second] = str[index];
		index++;
		matrix_second++;
	}
	return (matrix);
}

t_info	*map_info(t_info *info, char *buffer)
{
	int	result;

	result = 0;
	while (*buffer >= '0' && *buffer <= '9')
	{
		result *= 10;
		result += *buffer - '0';
		buffer++;
	}
	info->column_size = result;
	info->avaliable_char = *(buffer);
	info->obstacle = *(buffer + 1);
	info->writable_char = *(buffer + 2);
	return (info);
}

t_info	*read_from_file(char *file_name)
{
	t_info	*info;
	char	buffer[MAX_INT];
	char	**matrix;
	int		file_index;
	int		first_line_size;

	file_index = open(file_name, O_RDONLY);
	if (read(file_index, buffer, MAX_INT) == -1)
	{
		ft_putstr(MAP_ERROR);
		exit(1);
	}
	first_line_size = ft_strlen_with_point(buffer, '\n');
	matrix = split(&buffer[first_line_size]);
	info = (t_info *)malloc(sizeof(t_info));
	info->matrix = matrix;
	info = map_info(info, buffer);
	close(file_index);
	return (info);
}
