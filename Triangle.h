#pragma once
#include <MyVector3.h>
#include "MyMatrix4x4.h"
#include "MyMath.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "ImGuiManager.h"
#include "DrawUtils.h"

class Triangle{

private:

	Vec3f rotate_;
	Vec3f translate_;

	Vec3f kLocalVertex_[3];
	Vec3f screenVertex_[3];
	Vec3f ndcVertex_[3];

	Vec3f cross_;
	float dot_;

	Matrix4x4 worldMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;


public:

	Triangle();

	void Init();
	void Update();
	void Draw();

	void MakeWorldViewProjectionMatrix(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix);
	void MakeSceenVertex(const Matrix4x4& viewportMatrix);

};

