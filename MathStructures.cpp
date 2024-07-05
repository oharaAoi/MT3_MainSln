#include "MathStructures.h"

void Ball::Draw(const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix) {
	Sphere sphere{};
	sphere.center = pos;
	sphere.radius = radius;
	sphere.color = color;

	DrawSphere(sphere, viewProjection, viewportMatrix);
}
