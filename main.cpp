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
	// ↓ 線分
	// ---------------------------------------------------------------
	Segment segment{
		.origin{-0.5f, 0.5f, -0.5f},
		.diff{0.0f, 2.0f, 0.0f}
	};

	Ray ray{
		.origin{-0.5f, 0.5f, -0.5f},
		.diff{0.0f, 2.0f, 0.0f}
	};

	Line line{
		.origin{-0.5f, 0.5f, -0.5f},
		.diff{0.0f, 2.0f, 0.0f}
	};

	// ---------------------------------------------------------------
	// ↓ AABB
	// ---------------------------------------------------------------
	AABB aabb1{
		.min{-0.5f, -0.5f, -0.5f},
		.max{0.5f, 0.5f, 0.5f},
	};
	unsigned int color1 = WHITE;

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

		Vec3f start = Transform(Transform(segment.origin, camera_->GetViewProjectMatrix()), camera_->GetViewportMatrix());

		Vec3f end = Transform(
			Transform(
				Add(segment.origin, segment.diff),
				camera_->GetViewProjectMatrix()
			),
			camera_->GetViewportMatrix());

		// ------------------------ minとmaxが入れ替わらないように ------------------------ //
		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);

		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);

		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

		// ------------------------ 当たり判定 ------------------------ //

		if (IsCollision(aabb1, line)) {
			color1 = RED;
		} else {
			color1 = WHITE;
		}

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		DrawAABB(aabb1, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), color1);

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

		ImGui::Begin("Set");

		if (ImGui::TreeNode("AABB1")) {
			ImGui::DragFloat3("aabb1.min", &aabb1.min.x, 0.1f, 0.1f);
			ImGui::DragFloat3("aabb1.max", &aabb1.max.x, 0.1f, 0.1f);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Segment")) {
			ImGui::DragFloat3("segment.origin", &segment.origin.x, 0.1f, 0.1f);
			ImGui::DragFloat3("segment.diff", &segment.diff.x, 0.1f, 0.1f);
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
