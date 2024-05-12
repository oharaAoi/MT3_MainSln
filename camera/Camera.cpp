#include "Camera.h"

Camera::Camera() { Init(); }

void Camera::Init(){

	scale_ = { 1.0f, 1.0f, 1.0f };
	rotate_ = { 0.26f, 0.0f, 0.0f };
	//rotate_ = { 0.0f, 0.0f, 0.0f };
	translation_ = { 0.0f, 1.542f, -5.798f };

	target_ = { 0,0,0 };

	scaleMat_ = MakeScaleMatrix(scale_);
	matRot_ = MakeRotateXYZMatrix(rotate_);
	translateMat_ = MakeTranslateMatrix(translation_);

	debugCameraMode_ = true;

	//cameraMatrix_ = MakeAffineMatrix(scale_, rotate_, translation_);
	cameraMatrix_ = Multiply(Multiply(scaleMat_, matRot_), translateMat_);

	// ビュー行列
	viewMatrix_ = Inverse(cameraMatrix_);
	// 射影行列
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

	viewProjectMatrix_ = Multiply(viewMatrix_, projectionMatrix_);

	viewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);
}

void Camera::Update(){

	TransitionMove();

	if (debugCameraMode_) {
		RotateMove();
	}

	scaleMat_ = MakeScaleMatrix(scale_);
	translateMat_ = MakeTranslateMatrix(translation_);

	cameraMatrix_ = Multiply(Multiply(scaleMat_, matRot_), translateMat_);
	// ビュー行列
	viewMatrix_ = Inverse(cameraMatrix_);
	
	// 射影行列
	projectionMatrix_ = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);

	viewProjectMatrix_ = Multiply(viewMatrix_, projectionMatrix_);

	viewportMatrix_ = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
}

void Camera::Draw(){
	ImGui::Begin("window");

	ImGui::DragFloat3("cameraTranslate", &translation_.x, 0.01f);
	ImGui::DragFloat3("cameraRotate_ ", &rotate_.x, 0.01f);

	ImGui::DragFloat2("diff_ ", &rotateDiff_.x, 0.01f);
	ImGui::DragInt2("mousePos ", &mousePos_.x, 0.01f);

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			ImGui::InputFloat("matRot", &matRot_.m[i][j], 0.01f, 1.0f);
			ImGui::SameLine();
		}
		ImGui::NewLine();
	}

	ImGui::End();
}

/// <summary>
	/// カメラを動かす
	/// </summary>
void Camera::TransitionMove() {
	if (Novice::IsPressMouse(2)) {
		Vec2 pos{};
		Novice::GetMousePosition(&pos.x, &pos.y);

		diff_.x = static_cast<float>(pos.x - mousePos_.x);
		diff_.y = static_cast<float>(pos.y - mousePos_.y);

		const float speed = 0.02f;
		Vec3f move{};
		// カメラの向きを求める
		move = TransformNormal(Normalize({ diff_.x, diff_.y, 0 }) * speed, cameraMatrix_);

		translation_ += move;
		target_ += move;

	} else if(!Novice::IsPressMouse(2)) {
		Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);
	}
}

/// <summary>
/// カメラを回転させる
/// </summary>
void Camera::RotateMove() {
	if (Novice::IsPressMouse(1)) {
		Vec2 pos{};
		Vec3f normalizeDiff{};
		Vec3f offset = { 0.0f, 2.0f, -6.0f };
		const float speed = 0.015f;
		// マウスの位置を得る
		Novice::GetMousePosition(&pos.x, &pos.y);
		// マウスの移動量を求める
		rotateDiff_.x = static_cast<float>(pos.x - rotateMousePos_.x);
		rotateDiff_.y = static_cast<float>(pos.y - rotateMousePos_.y);
		// 正規化する
		normalizeDiff = Normalize({ rotateDiff_.x , rotateDiff_.y, 0 }) * speed;

		// 追加回転分の回転行列を生成
		Matrix4x4 matRotDelta = MakeIdentity4x4();
		matRotDelta *= MakeRotateXMatrix(normalizeDiff.y);
		matRotDelta *= MakeRotateYMatrix(normalizeDiff.x);

		// 累積の回転行列の合成
		matRot_ = matRotDelta * matRot_;

		/// -------------------------------------------------------------------------
		// 旋回させる
		offset = TransformNormal(Vec3f(0, 0, -6), matRot_);
		// 位置を動かす
		translation_ = target_ + offset;

		cameraMatrix_ = Multiply(Multiply(scaleMat_, matRot_), MakeTranslateMatrix(translation_));
		viewMatrix_ = Inverse(cameraMatrix_);

	} else if(!Novice::IsPressMouse(1)) {
		Novice::GetMousePosition(&rotateMousePos_.x, &rotateMousePos_.y);
	}
}