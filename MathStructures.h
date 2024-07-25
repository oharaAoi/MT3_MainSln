﻿#pragma once
#include "MyVector3.h"
#include "MyMatrix4x4.h"

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
};

// 振り子
struct Pendulum {
	Vec3f anchor; // アンカーポイント
	float length; // 紐の長さ
	float angle;  // 現在の角度
	float angularVelocity; // 角速度
	float angularAcceleration; // 角加速度
	Vec3f tipCenter; // 先端の位置
};

// 円錐振り子
struct ConicalPendulum {
	Vec3f anchor; // アンカーポイント
	float length; // 紐の長さ
	float halfApexAngle; // 円錐の頂角の半分
	float angle; // 現在の角度
	float angularVelocity; // 角加速度
};