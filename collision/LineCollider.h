#pragma once
#include "MyMath.h"
#include "MyMatrix4x4.h"
#include "DrawUtils.h"

/// <summary>///
/// 線分と平面の当たり判定
/// </summary>///
/// <param name="segment">線分</param>/// 
/// <param name="plane">平面</param>///
///  <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Segment& segment, const Plane& plane);

/// <summary>///
/// 直線と平面の当たり判定
/// </summary>///
/// <param name="segment">直線</param>/// 
/// <param name="plane">平面</param>///
///  <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Line& line, const Plane& plane);

/// <summary>///
/// 半直線と平面の当たり判定
/// </summary>///
/// <param name="segment">半直線</param>/// 
/// <param name="plane">平面</param>///
///  <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Ray& ray, const Plane& plane);

bool IsCollision(const Triangle& triangle, const Segment& segment);
bool IsCollision(const Triangle& triangle, const Ray& ray);
bool IsCollision(const Triangle& triangle, const Line& line);