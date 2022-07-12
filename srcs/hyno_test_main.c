/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyno_test_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyno <hyno@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:30:25 by hyno              #+#    #+#             */
/*   Updated: 2022/07/12 17:09:33 by hyno             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure.h"
#include "vec3.h"
#include "ray.h"
#include <stdlib.h>

static void	malloc_screen(t_color3 ***target, int x, int y)
{
	int		i;
	t_color3	**screen;

	screen = 0;
	screen = (t_color3 **)malloc(sizeof(t_color3 *) * y);
	if (screen == 0)
		ft_perror("malloc failed");
	i = 0;
	while (i < y)
	{
		screen[i] = 0;
		screen[i] = (t_color3 *)malloc(sizeof(t_color3) * x);
		if (screen[i] == 0)
			ft_perror("malloc failed");
	}
	*target = screen;
}

static void	malloc_ray(t_ray ***target, int x, int y)
{
	int		i;
	t_ray	**ray_arr;

	ray_arr = 0;
	ray_arr = (t_ray **)malloc(sizeof(t_ray *) * y);
	if (ray_arr == 0)
		ft_perror("malloc failed");
	i = 0;
	while (i < y)
	{
		ray_arr[i] = 0;
		ray_arr[i] = (t_ray *)malloc(sizeof(t_ray) * x);
		if (ray_arr[i] == 0)
			ft_perror("malloc failed");
	}
	*target =ray_arr;
}

#include "objects.h"
#include "vec3.h"
#include "float.h"

t_sphere	*new_sphere(t_vec3 origin, t_float radius, t_color3 color)
{
	t_sphere *rtn;

	rtn = malloc(sizeof(t_sphere));
	rtn->origin = origin;
	rtn->radius = radius;
	rtn->surf.color = color;
}

t_plane	*new_plane(t_vec3 origin, t_vec3 normal, t_color3 color)
{
	t_plane *rtn;

	rtn = malloc(sizeof(t_plane));
	rtn->origin = origin;
	rtn->normal = normal;
	rtn->surf.color = color;
}

t_dot_light	*new_dot_light(t_vec3 origin, int color)
{
	t_dot_light *rtn;

	rtn = malloc(sizeof(t_dot_light));
	rtn->origin = origin;
	rtn->color.x = color;
	rtn->color.y = color;
	rtn->color.z = color;
}

t_list	*ft_lstnew_type(void *content, int type)
{
	t_list	*rtn;
	rtn->content = content;
	rtn->next = 0;
	rtn->type = type;
	return (rtn);
}

void	hyno_test(t_data data)
{
	t_ray		**ray_arr;
	t_color3	**screen;

	ft_lstadd_front(data.object_list, ft_lstnew_type(new_sphere(vec3(1,1,1), 0.5, vec3(200, 100, 50)), SP));
	ft_lstadd_front(data.object_list, ft_lstnew_type(new_sphere(vec3(3,3,3), 1, vec3(10, 10, 200)), SP));

	ft_lstadd_front(data.dot_lights, ft_lstnew_type(new_dot_light(vec3(3,3,3), 222), SP));

	data.camera = malloc(sizeof(t_camera));
	data.camera->origin = vec3(0, 0, 0);
	data.ambient = vec3(0 , 20, 0);
	data.camera->direction = vec3(0, 0, -1);
	data.camera->horizontal = vec3(1, 0, 0);
	data.camera->vertical = vec3(0, 1, 0);
	data.camera->focal_len = 1;
	data.camera->left_bottom = vec3(-1, -1, -1);

	data.window.resolution_x = 1920;
	data.window.resolution_y = 1080;
	setting_default(data);
	malloc_ray(&ray_arr, data.setting->render_resolution_x, \
		data.setting->render_resolution_y);
	malloc_ray(&screen, data.setting->render_resolution_x, \
		data.setting->render_resolution_y);
	render_image_one(ray_arr, screen, data);
	draw_screen(screen, data);
}