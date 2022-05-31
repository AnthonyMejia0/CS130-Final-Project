#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
	vec3 color = world.ambient_color * world.ambient_intensity * color_ambient;

    for (unsigned i = 0; i < world.lights.size(); i++){
    	vec3 l = world.lights[i]->position - intersection_point;

    	if (world.enable_shadows){
    		Ray lightRay;
            lightRay.endpoint = intersection_point;
            lightRay.direction = l.normalized();
            Hit h = world.Closest_Intersection(lightRay);
            if (h.object != NULL){
				if(h.dist < l.magnitude()){
					continue;
				}
		    }
		}

    	vec3 R = (2 * dot(l, normal) * normal - l).normalized();
    	vec3 light_color = world.lights[i]->Emitted_Light(ray.direction) / l.magnitude_squared();
    	double diffuse_intensity = std::max(0.0, dot(normal, l.normalized()));
    	double specular_intensity = pow(std::max(0.0, dot(R, (ray.endpoint - intersection_point).normalized())), specular_power);
    	
    	vec3 diffuse = diffuse_intensity * color_diffuse * light_color;
    	vec3 specular = specular_intensity * color_specular * light_color;

    	color += diffuse + specular;
    }

    return color;
}
