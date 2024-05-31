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
	Vec3f rotate = { 45.0f, 0.0f, 0.0f };
	OBB obb{
		.center {-2.0f, 0.0f, 0.0f},
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
	// ↓ Sphere
	// ---------------------------------------------------------------
	Sphere sphere{
		.center{0.0f, 0.0f, 0.0f},
		.radius{0.5f},
		.color{WHITE}
	};


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

		// ------------------------ minとmaxが入れ替わらないように ------------------------ //
		/*aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);

		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);

		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);*/

		obb.MakeOBBAxis(rotate);

		// ------------------------ 当たり判定 ------------------------ //
		if (IsCollision(obb, sphere)) {
			obbColor = RED;
		} else {
			obbColor = WHITE;
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

		DrawSphere(sphere, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		ImGui::Begin("Set");

		if (ImGui::TreeNode("OBB")) {
			ImGui::DragFloat3("obb.center", &obb.center.x, 0.1f, 0.1f);
			ImGui::DragFloat3("rotate", &rotate.x, 1.0f);

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
