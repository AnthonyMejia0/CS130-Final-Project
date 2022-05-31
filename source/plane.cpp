#include "plane.h"
#include "ray.h"
#include <cfloat>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
Hit Plane::Intersection(const Ray& ray, int part) const
{
	Hit h = {0,0,0};

    double denom = dot(ray.direction, this->normal);
    if (denom != 0){
		vec3 diff = (this->x1 - ray.endpoint);
		double t = dot(diff, normal) / denom;

		if (t >= 0){
			h.object = this;
			h.dist = t;
			h.part = part;
		}
	}

    return h;
}

vec3 Plane::Normal(const vec3& point, int part) const
{
    return normal;
}

// There is not a good answer for the bounding box of an infinite object.
// The safe thing to do is to return a box that contains everything.
Box Plane::Bounding_Box(int part) const
{
    Box b;
    b.hi.fill(std::numeric_limits<double>::max());
    b.lo=-b.hi;
    return b;
}
