/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:22:04 by kanlee            #+#    #+#             */
/*   Updated: 2020/12/05 18:18:54 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "libft/libft.h"
#include "vec.h"
#include "color.h"

int		get_integer(char **line)
{
	int ret;
	int sign;

	sign = 1;
	if (**line == '-')
		sign = -1;
	if (**line == '-' || **line == '+')
		(*line)++;
	ret = 0;
	while (**line && ft_isdigit(**line))
	{
		ret = ret * 10 + **line - '0';
		(*line)++;
	}
	return (ret * sign);
}

double	get_double(char **line)
{
	double ret;
	double decimal;
	int sign;

	sign = 1;
	if (**line == '-')
		sign = -1;
	if (**line == '-' || **line == '+')
		(*line)++;
	ret = get_integer(line);
	decimal = 0.1;
	if (**line == '.')
	{
		(*line)++;
		while (**line && ft_isdigit(**line))
		{
			ret = ret + (**line - '0') * decimal;
			decimal /= 10;
			(*line)++;
		}
	}
	return (ret * sign);
}

t_color	get_color(char **line)
{
	t_color ret;

	ret.r = get_integer(line) / 255.0;
	skip_sep(line);
	ret.g = get_integer(line) / 255.0;
	skip_sep(line);
	ret.b = get_integer(line) / 255.0;
	return (ret);
}

t_vec	get_vector(char **line)
{
	t_vec ret;

	ret.x = get_double(line);
	skip_sep(line);
	ret.y = get_double(line);
	skip_sep(line);
	ret.z = get_double(line);
	return (ret);
}
