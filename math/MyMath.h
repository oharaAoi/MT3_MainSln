﻿#pragma once
#include "Vector2.h"
#include "MyVector3.h"
#include "Vector4.h"
#include "MyMatrix4x4.h"

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

//=================================================================================================================
//	↓	構造体
//=================================================================================================================
/// <summary>
/// 直線
/// </summary>
struct Line {
	Vec3f origin;	// 始点
	Vec3f diff;	// 終点への差分ベクトル
};

/// <summary>
/// 半直線
/// </summary>
struct Ray {
	Vec3f origin;	// 始点
	Vec3f diff;	// 終点への差分ベクトル
};

/// <summary>
/// 線分
/// </summary>
struct Segment {
	Vec3f origin;	// 始点
	Vec3f diff;	// 終点への差分ベクトル
};

Vec3f GetStartPoint(const Vec3f& startPos, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
Vec3f GetEndPoint(const Vec3f& endPos, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);


//=================================================================================================================
//	↓　四則演算
//=================================================================================================================
/// <summary>
/// 加算
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Add(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// 減算
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f  Subtract(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// 掛け算
/// </summary>
/// <param name="scalar"></param>
/// <param name="v"></param>
/// <returns></returns>
Vec3f Multiply(float scalar, const Vec3f& v);

//=================================================================================================================
//	↓	ベクトルの内積外積
//=================================================================================================================
/// <summary>
/// 内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// クロス積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Cross(const Vec3f& v1, const Vec3f& v2);

//=================================================================================================================
//	↓	ベクトルの長さに関する関数
//=================================================================================================================
/// <summary>
/// ノルム
/// </summary>
/// <param name="vec3"></param>
/// <returns></returns>
float Length(const Vec3f& vec3);

/// <summary>
/// 正規化
/// </summary>
/// <param name="vec3"></param>
/// <returns></returns>
Vec3f Normalize(const Vec3f& vec3);

void Normalize(Vec3f& v);

//=================================================================================================================
//	↓	ベクトルに関する関数
//=================================================================================================================
/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Project(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// 垂直なベクトルを返す関数
/// </summary>
/// <param name="vector">法線</param>
/// <returns>垂直ベクトル</returns>
Vec3f Perpendicular(const Vec3f& vector);

/// <summary>
/// 最近接点を求める関数
/// </summary>
/// <param name="point">点P(ここから線分へのベクトルをベクトル射影する)</param>
/// <param name="segment"></param>
/// <returns></returns>
Vec3f ClosestPoint(const Vec3f& point, const Segment& segment);

/// <summary>
/// ベクトル変換
/// </summary>
/// <param name="v"></param>
/// <param name="m"></param>
/// <returns></returns>
Vec3f TransformNormal(const Vec3f& v, const Matrix4x4& m);

Vec3f ApplyRotation(const Vec3f& direction, const Matrix4x4& mat);

//=================================================================================================================
//	↓ 曲線
//=================================================================================================================

/// <summary>
/// 線形補完
/// </summary>
/// <param name="p1">制御点1</param>
/// <param name="p2">制御点2</param>
/// <param name="t">時間</param>
/// <returns>p1をp2までにt時間分進めた値</returns>
Vec3f Lerp(const Vec3f& p1, const Vec3f& p2, const float& t);

/// <summary>
/// ベジエ曲線を書く
/// </summary>
///  <param name="controlPoint">制御点がまとまった配列</param>
///  <returns></returns>
Vec3f Bezier(const std::vector<Vec3f>& controlPoint, const float& t);