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

	// ---------------------------------------------------------------
	// ↓ OBB
	// ---------------------------------------------------------------
	Vec3f rotate = { 0.0f, 0.0f, 0.0f };
	OBB obb{
		.center {-1.0f, 0.0f, 0.0f},
		.orientations = {
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
		},
		.size{0.5f, 0.5f, 0.5f}
	};

	obb.MakeOBBAxis(rotate);

	uint32_t obbColor = WHITE;

	// ---------------------------------------------------------------
	// ↓ OBB2
	// ---------------------------------------------------------------
	Vec3f rotate2 = { -0.05f, -2.49f, 0.15f };
	OBB obb2{
		.center {0.9f, 0.66f, 0.78f},
		.orientations = {
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
		},
		.size{0.5f, 0.37f, 0.5f}
	};

	obb2.MakeOBBAxis(rotate2);

	uint32_t obbColor2 = WHITE;

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

		// ------------------------ OBBの回転要素を求める ------------------------ //

		obb.MakeOBBAxis(rotate);
		obb2.MakeOBBAxis(rotate2);

		// ------------------------ 当たり判定 ------------------------ //

		if (IsCollision(obb, obb2)) {
			obbColor2 = RED;
		} else {
			obbColor2 = WHITE;
		}


		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		DrawOBB(obb, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), obbColor);
		DrawOBB(obb2, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), obbColor2);

		ImGui::Begin("Set");

		if (ImGui::TreeNode("OBB1")) {
			ImGui::DragFloat3("obb.center", &obb.center.x, 0.1f, 0.1f);
			ImGui::DragFloat3("rotate", &rotate.x, 0.1f);
			ImGui::DragFloat3("size", &obb.size.x, 0.1f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("OBB2")) {
			ImGui::DragFloat3("obb.center", &obb2.center.x, 0.1f, 0.1f);
			ImGui::DragFloat3("rotate", &rotate2.x, 0.1f);
			ImGui::DragFloat3("size", &obb2.size.x, 0.1f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Segment")) {
			
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
