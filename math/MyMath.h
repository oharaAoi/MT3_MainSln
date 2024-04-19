﻿#pragma once
#include "Vector2.h"
#include "MyVector3.h"
#include "Vector4.h"

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

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

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Project(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// 最近接点を求める関数
/// </summary>
/// <param name="point">点P(ここから線分へのベクトルをベクトル射影する)</param>
/// <param name="segment"></param>
/// <returns></returns>
Vec3f ClosestPoint(const Vec3f& point, const Segment& segment);