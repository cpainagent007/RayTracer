#include "Sphere.h"

bool Sphere::Hit(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit) {
    // compute direction vector (ray origin - sphere center)
    glm::vec3 oc = ray.origin - transform.position;

    // quadratic coefficients for ray–sphere intersection
    // a coefficient is a number that multiplies a variable in a mathematical expression
    // for example: 3x + 5 <= the coefficient of x is 3
    float a = dot(ray.direction, ray.direction);
    float b = 2 * dot(ray.direction, oc);
    float c = glm::dot(oc, oc) - radius * radius;

    // discriminant tells us how many real intersection points exist :
    // discriminant => b² - 4ac
    // b² = (b * b)
    float discriminant = (b * b) - (4 * a * c);

    // discriminant of quadratic: < 0 no hit, = 0 tangent (one hit), > 0 two hits
    if (discriminant >= 0) {
        // quadratic formula gives possible ray–sphere intersection distances.
        //t = (-b ± sqrt(discriminant)) / (2a)

        // solve quadratic for the nearest intersection: t = (-b - sqrt(discriminant)) / (2a)
        // use the smaller root first (closest hit along the ray).
        float t = (-b - sqrt(discriminant)) / (2 * a);
        if (t > minDistance && t < maxDistance) {
            raycastHit.distance = t;
            raycastHit.point = ray.at(t);
            raycastHit.normal = glm::normalize(raycastHit.point - transform.position);

            raycastHit.material = material.get();

            return true;
        }
        // if the nearest root wasn't valid, check the second one: t = (-b + sqrt(discriminant)) / (2a)
        // this is the farther intersection point where the ray exits the sphere.
        t = (-b + sqrt(discriminant)) / (2 * a);
        if (t > minDistance && t < maxDistance) {
            raycastHit.distance = t;
            raycastHit.point = ray.at(t);
            raycastHit.normal = glm::normalize(raycastHit.point - transform.position);

            raycastHit.material = material.get();

            return true;
        }
    }

    return false;
}
