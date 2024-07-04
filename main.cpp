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
	
	Vec3f a{ 0.2f, 1.0f, 0.0f };
	Vec3f b{ 2.4f, 3.1f, 1.2f };
	Vec3f c = a + b;
	Vec3f d = a - b;
	Vec3f e = a * 2.4f;
	Vec3f rotate{ 0.4f, 1.43f, -0.8f };
	Matrix4x4 rotateXMat = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMat = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMat = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMat = rotateXMat * rotateYMat * rotateZMat;

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


		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		
		
		ImGui::Begin("Set");

		if (ImGui::TreeNode("point")) {	
			ImGui::TreePop();
		}

		ImGui::Text("c:%f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d:%f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e:%f, %f, %f", e.x, e.y, e.z);

		ImGui::Text(
			"matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f",
			rotateMat.m[0][0], rotateMat.m[0][1], rotateMat.m[0][2],
			rotateMat.m[0][3], rotateMat.m[1][0], rotateMat.m[1][1],
			rotateMat.m[1][2], rotateMat.m[1][3], rotateMat.m[2][0],
			rotateMat.m[2][1], rotateMat.m[2][2], rotateMat.m[2][3],
			rotateMat.m[3][0], rotateMat.m[3][1], rotateMat.m[3][2],
			rotateMat.m[3][3]
		);

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
