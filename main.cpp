#include <Novice.h>
#include "Matrix4x4.h"
#include "MyMath.h"
#include "DrawUtils.h"
#include "Camera.h"
#include <memory>
#include "SphereCollision.h"

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
	// sphereの初期化
	Sphere sphere1 = { { -1.0f, 0.0f, -1.0f}, 0.5f , 0xffffffff };
	Sphere sphere2 = { { 1.0f, 0.0f, 2.0f}, 0.5f , 0xffffffff };

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

		if (IsCollision(sphere1, sphere2)) {
			sphere1.color = 0xff0000ff;
		} else {
			sphere1.color = 0xffffffff;
		}



		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		DrawSphere(sphere1, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());
		DrawSphere(sphere2, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		ImGui::Begin("Setting");

		ImGui::Text("sphere1");
		ImGui::DragFloat3("Sphere1.center", &sphere1.center.x, 0.1f);
		ImGui::DragFloat("Sphere1.radius", &sphere1.radius, 0.1f);
		ImGui::Text("sphere2");
		ImGui::DragFloat3("Sphere2.center", &sphere2.center.x, 0.1f);
		ImGui::DragFloat("Sphere2.radius", &sphere2.radius, 0.1f);

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
