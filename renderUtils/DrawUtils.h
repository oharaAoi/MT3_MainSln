#pragma once
#include <Novice.h>
#include "MyMatrix4x4.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

struct Sphere {
	Vector3 center;
	float radius;
};

void DrawGrid(const Matrix4x4& viewPrijectionMatrix, const Matrix4x4& viewMatrix);

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);

// 表示
void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColWidth * 3, y, "%s", label);
}

