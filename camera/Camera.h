#pragma once
#include "MyVector2.h"
#include "MyMatrix4x4.h"
#include "MyVector3.h"
#include "MyMath.h"

#include "Environment.h"
#include "ImGuiManager.h"

class Camera{

private:

	Vec3f scale_;
	Vec3f translation_;
	Vec3f rotate_;

	Matrix4x4 translateMat_;
	Matrix4x4 scaleMat_;

	Matrix4x4 cameraMatrix_;
	// ビュー行列
	Matrix4x4 viewMatrix_;
	// 射影行列
	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectMatrix_;

	Matrix4x4 viewportMatrix_;

	// ------------------------------------------------------------- //
	// デバックカメラ用の変数
	// ------------------------------------------------------------- //
	// マウスの座標
	Vec2 mousePos_;
	Vec2 rotateMousePos_;
	// 差
	Vec2f diff_;
	Vec2f rotateDiff_;

	Matrix4x4 matRot_;

	bool debugCameraMode_;

public:

	Camera();

	void Init();
	void Update();
	void Draw();

public:

	void TransitionMove();

	void RotateMove();

	Vec3f GetCameraDirection(const Matrix4x4& rotationMatrix);

public:

	Matrix4x4 GetViewMatrix() const { return viewMatrix_; }
	Matrix4x4 GetProjectionMatrix() const { return projectionMatrix_; }
	Matrix4x4 GetViewportMatrix() const { return viewportMatrix_; }
	Matrix4x4 GetViewProjectMatrix() const { return viewProjectMatrix_; }

};

