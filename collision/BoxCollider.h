﻿#pragma once
#include "MyMath.h"
#include "MyMatrix4x4.h"
#include "DrawUtils.h"
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
