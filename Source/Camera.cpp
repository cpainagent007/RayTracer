#include "Camera.h"

void Camera::SetView(const glm::vec3& eye, const glm::vec3& target, const glm::vec3& up)
{
    this->eye = eye;
    forward = glm::normalize(target - eye);
    right = glm::normalize(glm::cross(forward, up));
    this->up = glm::normalize(glm::cross(right, forward));

    CalculateViewPlane();
}


ray_t Camera::GetRay(const glm::vec2& uv) const {
	ray_t ray;

	ray.origin = eye;
	ray.direction = (lowerLeft + (horizontal * uv.x) + (vertical * uv.y)) - eye;

	return ray;
}

void Camera::CalculateViewPlane() {
	float theta = glm::radians(fov);

	float halfHeight = glm::tan(theta * 0.5f);
	float halfWidth = halfHeight * aspectRatio;

	horizontal = right * (halfWidth * 2.0f);
	vertical = up * (halfHeight * 2.0f);

	lowerLeft = eye - (horizontal * 0.5f) - (vertical * 0.5f) + forward;
}

