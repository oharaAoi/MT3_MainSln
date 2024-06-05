#pragma once
#include "MyMath.h"
#include "MyMatrix4x4.h"
#include "DrawUtils.h"
#undef min
#undef max
#include <algorithm>

/// <summary>
/// 当たり判定
/// </summary>
/// <param name="aabb1">箱1</param>
/// <param name="aabb2">箱2</param>
/// <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const AABB& aabb1, const AABB& aabb2);

/// <summary>
/// 球との当たり判定
/// </summary>
/// <param name="aabb">箱</param>
/// <param name="sphere">球</param>
/// <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const AABB& aabb, const Sphere& sphere);

/// <summary>///
/// 線分との当たり判定
/// </summary>///
///  <param name="aabb">箱</param>
/// <param name="segment">線分</param>
/// <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const AABB& aabb, const Segment& segment);

/// <summary>///
/// 線分との当たり判定
/// </summary>///
/// <param name="aabb">箱</param>
/// <param name="Ray">半直線</param>
/// <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const AABB& aabb, const Ray& ray);

/// <summary>///
/// 線分との当たり判定
/// </summary>///
/// <param name="aabb">箱</param>
/// <param name="Line">直線</param>
/// <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const AABB& aabb, const Line& line);