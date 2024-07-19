#pragma once
#include <Novice.h>
#include "MyMatrix4x4.h"
#include "MyMath.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

/// <summary>
/// ワールド空間での線を引く
/// </summary>
/// <param name="startWorldPos"></param>
/// <param name="endWorldPos"></param>
/// <param name="viewPrijectionMatrix"></param>
/// <param name="viewMatrix"></param>
void DrawWorldLine(const Vec3f& startWorldPos, const Vec3f& endWorldPos, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewMatrix);

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

void DrawBall(const Ball& ball, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);

/// <summary>
/// 平面を引く関数
/// </summary>
/// <param name="plane"></param>
/// <param name="viewProjection"></param>
/// <param name="viewMatrix"></param>
/// <param name="color"></param>
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color);

/// <summary>
/// 三角形の描画
/// </summary>
/// <param name="triangle">頂点</param>
/// <param name="viewProjection">正射影行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
/// <param name="color">色</param>
/// <param name="isWier">塗りつぶすか</param>
void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color, const bool& isWier);

/// <summary>
/// AABB(軸平行境界箱)
/// </summary>
/// <param name="aabb">AABB(軸平行境界箱)</param>
/// <param name="viewProjection">正射影行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
/// <param name="color">色</param>
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color);

/// <summary>
/// 
/// </summary>
/// <param name="obb"></param>
/// <param name="viewProjection"></param>
/// <param name="viewportMatrix"></param>
/// <param name="color"></param>
void DrawOBB(const OBB& obb, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color);

/// <summary>
/// 2次ベジエ曲線を書く
/// </summary>
/// <param name="controlPoint">制御点の配列</param>
/// <param name="viewProjectionMat">ビュープロジェクション</param>
/// <param name="viewportMat">ビューポート</param>
/// <param name="color">カラー</param>
//void DrawBezier(const std::vector<Vec3f>& controlPoint, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, const uint32_t& color);
void DrawBezier(const Vec3f& control0, const Vec3f& control1, const Vec3f& control2, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, const uint32_t& color);
void DrawBezier(std::vector<Vec3f> controlPoints, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, const uint32_t& color);

void DrawCatmullRom(const Vec3f& control0, const Vec3f& control1, const Vec3f& control2, const Vec3f& control3, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, const uint32_t& color);

// 表示
void VectorScreenPrintf(int x, int y, const Vec3f& vector, const char* label);
