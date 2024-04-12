#pragma once
#include <Novice.h>
#include "MyMatrix4x4.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

struct Sphere {
	Vec3f center;
	float radius;
};

void DrawGrid(const Matrix4x4& viewPrijectionMatrix, const Matrix4x4& viewMatrix);

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

// 表示
void VectorScreenPrintf(int x, int y, const Vec3f& vector, const char* label);
