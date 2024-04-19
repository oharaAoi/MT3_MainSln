#pragma once
#include <Novice.h>
#include <MyVector3.h>
#include "MyMatrix4x4.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "ImGuiManager.h"

class Triangle{

private:

	Vec3f rotate_;
	Vec3f translate_;

	Vec3f kLocalVertex_[3];
	Vec3f screenVertex_[3];

	Matrix4x4 worldMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;


public:

	Triangle();

	void Init();
	void Update(char* keys);
	void Draw();

	void MakeWorldViewProjectionMatrix(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix);
	void MakeSceenVertex(const Matrix4x4& viewportMatrix);

};

