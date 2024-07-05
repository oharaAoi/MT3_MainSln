#pragma once
#include "MyVector3.h"
#include "MyMath.h"
#include "MyMatrix4x4.h"
#include "DrawUtils.h"

struct Spring {
	// アンカー。固定された橋の位置
	Vec3f anchor;
	float naturalLength; // 自然長
	float stiffness;	 // 剛性。ばね定数k
	float dampingCoefficient; // 減衰係数
};

struct Ball {
	Vec3f pos;			// ボールの位置
	Vec3f velocity;		// ボールの速度
	Vec3f acceleration;	// 加速度
	float mass;			// 質量
	float radius;		// 半径
	unsigned int color;	// 色

	void Draw(const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix);
};

