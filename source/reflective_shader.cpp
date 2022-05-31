#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    double ref = 1 - reflectivity;
    color = shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);

    if (recursion_depth < world.recursion_depth_limit){
    	Ray r;
    	r.endpoint = intersection_point;
    	r.direction = ray.direction - 2 * dot(normal, ray.direction) * normal;

    	color = ref * color + reflectivity * world.Cast_Ray(r, ++recursion_depth);
    }
    else {
    	color *= ref;
    }

   	return color;
}
