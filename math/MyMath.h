#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

Vector3 Add(const Vector3& v1, const Vector3& v2);

Vector3  Subtract(const Vector3& v1, const Vector3& v2);

Vector3 Multiply(float scalar, const Vector3& v);

float Dot(const Vector3& v1, const Vector3& v2);

float Length(const Vector3& vec3);

Vector3 Normalize(const Vector3& vec3);
