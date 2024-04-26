#pragma once
#include <Novice.h>
#include "MyMatrix4x4.h"
#include "MyMath.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

struct Sphere {
	Vec3f center;
	float radius;
	uint32_t color;
};

/// <summary>
/// 平面
/// </summary>
struct Plane {
	Vec3f normal;	// 法線
	float distance;	// 距離
};

/// <summary>
/// グリット線を引く関数
/// </summary>
/// <param name="viewPrijectionMatrix"></param>
/// <param name="viewMatrix"></param>
void DrawGrid(const Matrix4x4& viewPrijectionMatrix, const Matrix4x4& viewMatrix);

/// <summary>
/// スフィアを描画する関数
/// </summary>
/// <param name="sphere"></param>
/// <param name="viewProjectionMatrix"></param>
/// <param name="viewportMatrix"></param>
void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// <summary>
/// 平面を引く関数
/// </summary>
/// <param name="plane"></param>
/// <param name="viewProjection"></param>
/// <param name="viewMatrix"></param>
/// <param name="color"></param>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color);

// 表示
void VectorScreenPrintf(int x, int y, const Vec3f& vector, const char* label);
