#include <Novice.h>
#include "Matrix4x4.h"
#include "MyMath.h"
#include "DrawUtils.h"
#include "Camera.h"
#include <memory>
#include <string>
#include "SphereCollision.h"
#include "LineCollider.h"
#include "BoxCollider.h"

const char kWindowTitle[] = "LE2A_06_オオハラアオイ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	int windowX = 1280;
	int windowY = 720;
	Novice::Initialize(kWindowTitle, windowX, windowY);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	std::unique_ptr<Camera> camera_ = std::make_unique<Camera>();

	// ---------------------------------------------------------------
	// ↓ 
	// ---------------------------------------------------------------
	Vec3f translates[3] = {
		{0.2f, 1.0f, 0.0f},
		{0.4f, 0.0f, 0.0f},
		{0.3f, 0.0f, 0.0f},
	};

	Vec3f rotates[3] = {
		{0.0f, 0.0f, -6.8f},
		{0.4f, 0.0f, -1.4f},
		{0.3f, 0.0f, 0.0f},
	};

	Vec3f scales[3] = {
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f},
	};

	Sphere sphere[3];
	for (uint32_t oi = 0; oi < 3; oi++) {
		// 色
		int color[3] = { 0 };
		color[oi] = 0xff;
		unsigned int finalColor = (color[0] << 24) | (color[1] << 16) | (color[2] << 8) | 0xff;

		sphere[oi] = {
			translates[oi],
			0.08f,
			finalColor
		};
	}

	// ---------------------------------------------------------------
	// ↓ 
	// ---------------------------------------------------------------

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///------------------///
		/// ↓更新処理ここから
		///------------------///

		camera_->Update();

		// ------------------------  ------------------------ //

		Matrix4x4 matShoulder = MakeAffineMatrix(scales[0], rotates[0], translates[0]);
		Matrix4x4 matElbow = MakeAffineMatrix(scales[1], rotates[1], translates[1]) * matShoulder;
		Matrix4x4 matHand = MakeAffineMatrix(scales[2], rotates[2], translates[2]) * matElbow;

		sphere[0].center = { matShoulder.m[3][0],matShoulder.m[3][1], matShoulder.m[3][2] };
		sphere[1].center = { matElbow.m[3][0],matElbow.m[3][1], matElbow.m[3][2] };
		sphere[2].center = { matHand.m[3][0],matHand.m[3][1], matHand.m[3][2] };
		
		Matrix4x4 wvpShoulder = matShoulder * camera_->GetViewProjectMatrix() * camera_->GetViewportMatrix();
		Matrix4x4 wvpElbow = matElbow * camera_->GetViewProjectMatrix() * camera_->GetViewportMatrix();
		Matrix4x4 wvpHand = matHand * camera_->GetViewProjectMatrix() * camera_->GetViewportMatrix();

		Vec3f screenPos[3] = {
			Transform({0,0,0}, wvpShoulder),
			Transform({0,0,0}, wvpElbow),
			Transform({0,0,0}, wvpHand),
		};

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		for (uint32_t oi = 0; oi < 3; oi++) {
			DrawSphere(sphere[oi], camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());
		}

		Novice::DrawLine(
			static_cast<int>(screenPos[0].x),
			static_cast<int>(screenPos[0].y),
			static_cast<int>(screenPos[1].x),
			static_cast<int>(screenPos[1].y),
			WHITE
		);

		Novice::DrawLine(
			static_cast<int>(screenPos[1].x),
			static_cast<int>(screenPos[1].y),
			static_cast<int>(screenPos[2].x),
			static_cast<int>(screenPos[2].y),
			WHITE
		);
		
		ImGui::Begin("Set");

		if (ImGui::TreeNode("point")) {
			for (uint32_t oi = 0; oi < 3; oi++) {
				std::string num = std::to_string(oi);

				std::string scaleLabel = "scale[" + num + "]";
				ImGui::DragFloat3(scaleLabel.c_str(), &scales[oi].x, 0.01f);
				// rotate
				std::string rotateLabel = "rotate[" + num + "]";
				ImGui::DragFloat3(rotateLabel.c_str(), &rotates[oi].x, 0.01f);
				// translate
				std::string translateLabel = "translate[" + num + "]";
				ImGui::DragFloat3(translateLabel.c_str(), &translates[oi].x, 0.01f);
				ImGui::Spacing();
			}
			ImGui::TreePop();
		}

		ImGui::End();


		///------------------///
		/// ↑描画処理ここまで
		///------------------///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
