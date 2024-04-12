#include "Camera.h"

Camera::Camera() { Init(); }

void Camera::Init(){

	pos_ = { 0.0f, 1.9f, -6.49f };
	rotate_ = { 0.26f, 0.0f, 0.0f };

	cameraMatrix_ = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate_, pos_);

	viewMatrix_ = Inverse(cameraMatrix_);

	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

	viewProjectMatrix_ = Multiply(viewMatrix_, projectionMatrix_);

	viewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

}

void Camera::Update(){

	cameraMatrix_ = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate_, pos_);

	viewMatrix_ = Inverse(cameraMatrix_);

	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

	viewProjectMatrix_ = Multiply(viewMatrix_, projectionMatrix_);

	viewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
}

void Camera::Draw(){
	ImGui::Begin("window");

	ImGui::DragFloat3("cameraTranslate", &pos_.x, 0.01f);
	ImGui::DragFloat3("cameraRotate_ ", &rotate_.x, 0.01f);

	ImGui::End();
}
