#pragma once
#include "MyMatrix4x4.h"
#include "Vector3.h"

#include "Environment.h"
#include "ImGuiManager.h"

class Camera{

private:

	Vector3 pos_;
	Vector3 rotate_;

	Matrix4x4 cameraMatrix_;

	Matrix4x4 viewMatrix_;

	Matrix4x4 projectionMatrix_;

	Matrix4x4 viewProjectMatrix_;

	Matrix4x4 viewportMatrix_;

public:

	Camera();

	void Init();
	void Update();
	void Draw();

	Matrix4x4 GetViewMatrix() const { return viewMatrix_; }
	Matrix4x4 GetProjectionMatrix() const { return projectionMatrix_; }
	Matrix4x4 GetViewportMatrix() const { return viewportMatrix_; }
	Matrix4x4 GetViewProjectMatrix() const { return viewProjectMatrix_; }

};

