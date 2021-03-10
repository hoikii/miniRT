/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanlee <kanlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 16:22:04 by kanlee            #+#    #+#             */
/*   Updated: 2021/03/10 17:49:25 by kanlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_utils.h"
#include "libft/libft.h"
#include "vec.h"
#include "color.h"

int		get_integer(char *str, int *ret)
{
	int	sign;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	*ret = 0;
	while (*str && *str != '.')
	{
		if (!ft_isdigit(*str))
			return (FAIL);
		*ret = *ret * 10 + *str - '0';
		str++;
	}
	*ret *= sign;
	return (SUCCESS);
}

int		get_double(char *str, double *ret)
{
	double	decimal;
	int		integral;
	int		sign;

	sign = 1;
	if (*str == '-')
		sign = -1;
	if (get_integer(str, &integral) == FAIL)
		return (FAIL);
	*ret = integral * sign;
	while (*str && *str != '.')
		str++;
	decimal = 1.0;
	if (*str == '.')
	{
		while (*(++str))
		{
			if (!ft_isdigit(*str))
				return (FAIL);
			*ret = *ret + (*str - '0') * (decimal /= 10);
		}
	}
	*ret *= sign;
	return (SUCCESS);
}

int		get_color(char *str, t_color *ret)
{
	int		r;
	int		g;
	int		b;
	char	**words;

	if (ft_cntwords(str, ',') != 3)
		return (FAIL);
	words = ft_split(str, ',');
	if ((get_integer(words[0], &r) == FAIL)
		|| (get_integer(words[1], &g) == FAIL)
		|| (get_integer(words[2], &b) == FAIL))
		return (FAIL);
	if (!(0 <= r && r <= 255 && 0 <= g && g <= 255 && 0 <= b && b <= 255))
		return (FAIL);
	ret->r = r / 255.0;
	ret->g = g / 255.0;
	ret->b = b / 255.0;
	free_words(words);
	return (SUCCESS);
}

int		get_vector(char *str, t_vec *ret)
{
	double	x;
	double	y;
	double	z;
	char	**words;

	if (ft_cntwords(str, ',') != 3)
		return (FAIL);
	words = ft_split(str, ',');
	if ((get_double(words[0], &x) == FAIL)
		|| (get_double(words[1], &y) == FAIL)
		|| (get_double(words[2], &z) == FAIL))
		return (FAIL);
	ret->x = x;
	ret->y = y;
	ret->z = z;
	free_words(words);
	return (SUCCESS);
}

int		get_vector_norm(char *str, t_vec *ret)
{
	double	x;
	double	y;
	double	z;
	char	**words;

	if (ft_cntwords(str, ',') != 3)
		return (FAIL);
	words = ft_split(str, ',');
	if ((get_double(words[0], &x) == FAIL)
		|| (get_double(words[1], &y) == FAIL)
		|| (get_double(words[2], &z) == FAIL))
		return (FAIL);
	if (!(-1 <= x && x <= 1) || !(-1 <= y && y <= 1)
		|| !(-1 <= z && z <= 1) || (x == 0 && y == 0 && z == 0))
		return (FAIL);
	ret->x = x;
	ret->y = y;
	ret->z = z;
	*ret = v_unit(*ret);
	free_words(words);
	return (SUCCESS);
}
