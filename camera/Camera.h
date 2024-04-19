#pragma once
#include "MyMatrix4x4.h"
#include "MyVector3.h"

#include "Environment.h"
#include "ImGuiManager.h"

class Camera{

private:

	Vec3f pos_;
	Vec3f rotate_;

	Matrix4x4 cameraMatrix_;

	Matrix4x4 viewMatrix_;

	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectMatrix_;

	Matrix4x4 viewportMatrix_;

	Vec3f dire_;

	Matrix4x4 cameraRotateMat;

public:

	Camera();

	void Init();
	void Update();
	void Draw();

	Matrix4x4 GetViewMatrix() const { return viewMatrix_; }
	Matrix4x4 GetProjectionMatrix() const { return projectionMatrix_; }
	Matrix4x4 GetViewportMatrix() const { return viewportMatrix_; }
	Matrix4x4 GetViewProjectMatrix() const { return viewProjectMatrix_; }

	Vec3f GetDirection() const { return dire_; }
};

