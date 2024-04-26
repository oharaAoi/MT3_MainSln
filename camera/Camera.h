#pragma once
#include "MyVector2.h"
#include "MyMatrix4x4.h"
#include "MyVector3.h"

#include "Environment.h"
#include "ImGuiManager.h"

class Camera{

private:

	Vec3f translation_;
	Vec3f rotate_;

	Matrix4x4 cameraMatrix_;
	// ビュー行列
	Matrix4x4 viewMatrix_;
	// 射影行列
	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectMatrix_;

	Matrix4x4 viewportMatrix_;

	// マウスの座標
	Vec2 mousePos_;

public:

	Camera();

	void Init();
	void Update();
	void Draw();

public:

	void RotateMove();

public:

	Matrix4x4 GetViewMatrix() const { return viewMatrix_; }
	Matrix4x4 GetProjectionMatrix() const { return projectionMatrix_; }
	Matrix4x4 GetViewportMatrix() const { return viewportMatrix_; }
	Matrix4x4 GetViewProjectMatrix() const { return viewProjectMatrix_; }

};

