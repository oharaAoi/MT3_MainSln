#pragma once
#include "MyMath.h"
#include "MyMatrix4x4.h"
#include "DrawUtils.h"
#include "MathStructures.h"
#include "LineCollider.h"

/// <summary>///
/// 球同士の当たり判定
/// </summary>///
/// <param name="s1">球1</param>///
/// <param name="s2">球2</param>///
/// <returns></returns>
bool IsCollision(const Sphere& s1, const Sphere& s2);

/// <summary>/// 
/// 球と平面の当たり判定
/// </summary>/// 
/// <param name="s1">球1</param>/// 
/// <param name="p1">平面1</param>/// 
/// <returns>true:当たっている　false:当たっていない</returns>
bool IsCollision(const Sphere& s1, const Plane& p1);

/// <summary>///
/// 
/// </summary>/// 
/// <param name="sphere"></param>///
///  <param name="capsule"></param>///
///  <returns></returns>
bool IsCollisionCapsule(const Ball& ball, const Plane& p1);

Vec3f BackBall(const Ball& ball, const Plane& p1);