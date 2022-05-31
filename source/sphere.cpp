#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
	Hit h = {0,0,0};
    vec3 v = ray.endpoint - this->center;
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(ray.direction, v);
    double c = dot(v, v) - (this->radius * this->radius);
    double d = b*b - 4*a*c;

    if (d >= 0.0){
   		double t = (-b - sqrt(d)) / (2.0*a);
   		h.object = this;
   		h.dist = t;
   		h.part = part;
 	}

    return h;
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    //TODO; // compute the normal direction
    normal = (point - center).normalized();
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}
