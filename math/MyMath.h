#pragma once
#include "Vector2.h"
#include "MyVector3.h"
#include "Vector4.h"

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

Vec3f Add(const Vec3f& v1, const Vec3f& v2);

Vec3f  Subtract(const Vec3f& v1, const Vec3f& v2);

Vec3f Multiply(float scalar, const Vec3f& v);

float Dot(const Vec3f& v1, const Vec3f& v2);

Vec3f Cross(const Vec3f& v1, const Vec3f& v2);

float Length(const Vec3f& vec3);

Vec3f Normalize(const Vec3f& vec3);
