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
#include "MathStructures.h"

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
	Ball ball{};
	ball.pos = { 1.0f, 0.0f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;

	// ---------------------------------------------------------------
	// ↓ 
	// ---------------------------------------------------------------
	ConicalPendulum conicalPendulum;
	conicalPendulum.anchor = { 0.0f, 1.0f, 0.0f };
	conicalPendulum.length = 0.8f;
	conicalPendulum.halfApexAngle = 0.7f;
	conicalPendulum.angle = 0.0f;
	conicalPendulum.angularVelocity = 0.0f;

	float deltaTime = 1.0f / 60.0f;

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

		// ------------------------ 振り子の角度を求める ------------------------ //
		conicalPendulum.angularVelocity = std::sqrt(9.8f / (conicalPendulum.length * std::cos(conicalPendulum.halfApexAngle)));
		conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;

		// ------------------------ 先端の位置を求める ------------------------ //
		float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
		float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;

		ball.pos.x = conicalPendulum.anchor.x + std::cos(conicalPendulum.angle) * radius;
		ball.pos.y = conicalPendulum.anchor.y - height;
		ball.pos.z = conicalPendulum.anchor.z - std::sin(conicalPendulum.angle) * radius;

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		DrawWorldLine(conicalPendulum.anchor, ball.pos, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		ball.Draw(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());
		
		ImGui::Begin("Set");

		if (ImGui::TreeNode("point")) {	
			ImGui::DragFloat("conicalPendulum.halfApexAngle", &conicalPendulum.halfApexAngle, 0.01f, 0, 2);
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
