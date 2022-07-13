#ifndef OBJECTS_H_
# define OBJECTS_H_

# include "libft.h"
# include "vec3.h"
# include "structure.h"
# include "ray.h"

typedef struct s_dot_light t_dot_light;
typedef struct s_surf      t_surf;
typedef struct s_sphere    t_sphere;
typedef struct s_plane     t_plane;
typedef struct s_cylinder  t_cylinder;
typedef struct s_ray	t_ray;


struct s_dot_light
{
    t_point3    origin;
    t_color3    color;
};

struct s_surf
{
    t_color3    color;
};

struct s_sphere
{
    t_point3    origin;
    t_float     radius;
    t_surf      surf;
};

struct s_plane
{
    t_point3    origin;
    t_vec3      normal;
    t_surf      surf;
};

struct s_cylinder
{
    t_point3    origin;
    t_vec3      normal;
    t_float     radius;
    t_float     height;
    t_surf      surf;
};

struct s_ray
{
	t_point3	point;
	t_vec3		direction;
	t_float		refractive;
};

#endif