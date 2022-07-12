/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complict.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyno <hyno@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:29:11 by hyno              #+#    #+#             */
/*   Updated: 2022/07/12 13:29:34 by hyno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "float.h"
#include "ray.h"
#include "structure.h"
#include "objects.h"
#include "vec3.h"

static t_float	get_dist_from_object(t_ray ray, t_list *head, t_data data)
{
	t_float dist;
	
	dist = 0;
	if (head->type == SP)
		dist = hit_sphere(conv_sp(head)->origin, conv_sp(head)->radius, ray);
	else if (head->type == PL)
		dist = hit_plane(conv_pl(head)->origin, conv_pl(head)->normal, ray);
	else if (head->type == CY)
		dist = hit_cylinder();
	return (dist);
}

static t_float	complict_all(t_ray ray, t_list *head, t_list **hit_object, t_data data)
{
	t_float temp;
	t_float dist;
	t_bool	is_hit;

	is_hit = FALSE;
	while (head)
	{
		temp = get_dist_from_object(ray, head, data);
		if (temp > 0)
		{
			is_hit = TRUE;
			dist = temp;
			*hit_object = head;
		}
		head = head->next;
	}
	if (is_hit == TRUE)
		return (dist);
	return (-1);
}

// dev_comment
// 이시점전에 plane의 노말벡터는 유닛벡터임이 보증되어있도록 하시오
// 실린더, 콘의 경우 추가하기
static void	set_hit_record(t_ray ray, t_list *hit_object, t_hit_record *hit_record)
{
	hit_record->hit_point = ray_at(ray, hit_record->dist);
	if (hit_object->type == SP)
	{
		hit_record->normal_unit = vec3_minus(hit_record->hit_point, conv_sp(hit_object)->origin);
		hit_record->normal_unit = vec3_unit(hit_record->normal_unit);
		hit_record->surf = conv_sp(hit_object)->surf;
	}
	else if (hit_object->type == PL)
	{
		hit_record->normal_unit = conv_pl(hit_object)->normal;
		hit_record->surf = conv_pl(hit_object)->surf;
	}
}

// dev_comment
// 충돌 최적화 함수를 새로 만들고 여기에 추가하시오
int	complict(t_ray ray, t_data data, t_hit_record *hit_record)
{
	t_list *hit_object;
	
	hit_object = 0;
	hit_record->dist = complict_all(ray, data.object_list, &hit_object, data);
	if (hit_object)
	{
		set_hit_record(ray, hit_object, hit_record);
		return (TRUE);
	}
	return (FALSE);
}