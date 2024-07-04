#include <Novice.h>
#include "Matrix4x4.h"
#include "MyMath.h"
#include "DrawUtils.h"
#include "Camera.h"
#include <memory>
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

	const int pointNum = 4;

	// ---------------------------------------------------------------
	// ↓ 
	// ---------------------------------------------------------------
	Vec3f controlPoint[4] = {
		{-0.8f, 0.58f, 1.0f},
		{1.76f, 1.0f, -0.3f},
		{0.94f, -0.7f, 2.3f},
		{-0.53f, -0.26f, -0.15f},
	};

	std::vector<Vec3f> controlPointArray_ = {
		{-0.8f, 0.58f, 1.0f},
		{1.76f, 1.0f, -0.3f},
		{0.94f, -0.7f, 2.3f},
		{-0.53f, -0.26f, -0.15f},
	};

	// ---------------------------------------------------------------
	// ↓ 
	// ---------------------------------------------------------------
	Sphere sphere[pointNum]{};
	for (uint8_t oi = 0; oi < pointNum; oi++) {
		sphere[oi] = {
		controlPointArray_[oi],
		0.05f,
		BLACK
		};
	}

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

		for (uint8_t oi = 0; oi < pointNum; oi++) {
			sphere[oi] = {
			controlPointArray_[oi],
			0.05f,
			BLACK
			};
		}

		// ------------------------  ------------------------ //

		// ------------------------ 当たり判定 ------------------------ //

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		/*DrawCatmullRom(controlPoint[0], controlPoint[0], controlPoint[1], controlPoint[2], camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), WHITE);
		DrawCatmullRom(controlPoint[0], controlPoint[1], controlPoint[2], controlPoint[3], camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), WHITE);
		DrawCatmullRom(controlPoint[1], controlPoint[2], controlPoint[3], controlPoint[3], camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), WHITE);*/

		DrawBezier(controlPointArray_, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), WHITE);

		for (uint8_t oi = 0; oi < pointNum; oi++) {
			DrawSphere(sphere[oi], camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());
		}
		
		ImGui::Begin("Set");

		if (ImGui::TreeNode("point")) {
			ImGui::DragFloat3("point0", &controlPointArray_[0].x, 0.01f);
			ImGui::DragFloat3("point1", &controlPointArray_[1].x, 0.01f);
			ImGui::DragFloat3("point2", &controlPointArray_[2].x, 0.01f);
			ImGui::DragFloat3("point3", &controlPointArray_[3].x, 0.01f);
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
