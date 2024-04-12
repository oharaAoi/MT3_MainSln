#include "MyMath.h"

float Length(const Vec3f& vec3){
    return std::sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
}

// 加算
Vec3f Add(const Vec3f& v1, const Vec3f& v2) {
	Vec3f result{};

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

// 減算
Vec3f  Subtract(const Vec3f& v1, const Vec3f& v2) {
	Vec3f result{};

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

// スカラー倍
Vec3f Multiply(float scalar, const Vec3f& v) {
	Vec3f result{};

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;

	return result;
}

// 内積
float Dot(const Vec3f& v1, const Vec3f& v2) {
	float result{};

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return result;
}

Vec3f Normalize(const Vec3f& vec3){
    Vec3f result = vec3;

    float len = Length(vec3);
    if (len != 0) {
        result.x /= len;
        result.y /= len;
        result.z /= len;
    }

    return result;
}
