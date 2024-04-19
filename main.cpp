#include <Novice.h>
#include <memory>
#include "Matrix4x4.h"
#include "MyMath.h"
#include "DrawUtils.h"
#include "Triangle.h"
#include "Camera.h"
#include "Environment.h"

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

	std::unique_ptr<Triangle> triangle_ = std::make_unique<Triangle>();
	std::unique_ptr<Camera> camera_ = std::make_unique<Camera>();

	Vec3f v1{ 1.2f, -3.9f, 2.5f };
	Vec3f v2{ 2.8f, 0.4f, -1.3f };

	Vec3f cross = Cross(v1, v2);


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


		triangle_->Update(keys);
		camera_->Update();

		triangle_->MakeWorldViewProjectionMatrix(camera_->GetViewMatrix(), camera_->GetProjectionMatrix());
		triangle_->MakeSceenVertex(camera_->GetViewportMatrix());

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		triangle_->Draw();
		camera_->Draw();

		VectorScreenPrintf(0, 0, cross, "Cross");

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
