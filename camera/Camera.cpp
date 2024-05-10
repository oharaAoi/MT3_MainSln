#include "Camera.h"

Camera::Camera() { Init(); }

void Camera::Init(){

	scale_ = { 1.0f, 1.0f, 1.0f };
	rotate_ = { 0.26f, 0.0f, 0.0f };
	//rotate_ = { 0.0f, 0.0f, 0.0f };
	translation_ = { 0.0f, 1.9f, -6.49f };

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

	/*if (Novice::IsTriggerMouse(1)) {
		if (debugCameraMode_) {
			debugCameraMode_ = false;
		} else {
			debugCameraMode_ = true;
		}
	}*/

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

	ImGui::End();
}

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

	} else if(!Novice::IsPressMouse(2)) {
		Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);
	}
}

void Camera::RotateMove() {
	if (Novice::IsPressMouse(1)) {
		Vec2 pos{};
		Vec3f normalizeDiff{};
		Vec3f offset = { 0.0f, 1.9f, -6.49f };
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
		matRotDelta = Multiply(matRotDelta, MakeRotateXMatrix(normalizeDiff.y));
		matRotDelta = Multiply(matRotDelta, MakeRotateYMatrix(normalizeDiff.x));

		// 累積の回転行列の合成
		matRot_ = matRotDelta * matRot_;

		/// -------------------------------------------------------------------------
		Vec3f dire = TransformNormal(Vec3f(0, 0, 1), matRot_);
		
		// ビューポート行列
		//Matrix4x4 matViewport = MakeViewportMatrix(0, 0, 1280, 720, 0, 1);
		//// viewprojectionViewport合成行列
		//Matrix4x4 matVPV = viewMatrix_ * projectionMatrix_ * matViewport;
		//// 合成行列の逆行列を計算する
		//Matrix4x4 matInverseVPV = Inverse(matVPV);

		//// ニアクリップ面上のワールド座標を得る
		//Vec3f posNear = Vec3f(static_cast<float>(640), static_cast<float>(360), 0);
		//// ファークリップ面上のワールド座標を得る
		//Vec3f posFar = Vec3f(static_cast<float>(640), static_cast<float>(360), 1);

		//// スクリーンからワールドへ
		//posNear = Transform(posNear, matInverseVPV);
		//posFar = Transform(posFar, matInverseVPV);

		//// mouseレイの方向
		//Vec3f mouseDirection = posFar - posNear;
		//mouseDirection = Normalize(mouseDirection);
		//// カメラから照準オブジェクトの距離
		//const float kDistanceTestObject = 6.0f;
		//Vec3f centerPos = posNear + mouseDirection * kDistanceTestObject;

		// -------------------------------------------------------------------------------
		offset = TransformNormal(offset, matRot_);
		Vec3f centerPos = translation_ + offset;
		
		translation_ = centerPos + offset;

		cameraMatrix_ = Multiply(Multiply(scaleMat_, matRot_), MakeTranslateMatrix(translation_));
		viewMatrix_ = Inverse(cameraMatrix_);

	} else if(!Novice::IsPressMouse(1)) {
		Novice::GetMousePosition(&rotateMousePos_.x, &rotateMousePos_.y);
	}
}

Vec3f Camera::GetCameraDirection(const Matrix4x4& rotationMatrix) {
	// カメラの向いている方向は回転行列の3つ目の列を取り出す
	return { rotationMatrix.m[0][2], rotationMatrix.m[1][2], rotationMatrix.m[2][2] };
}