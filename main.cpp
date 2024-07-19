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
	ball.pos = { 0.8f, 1.2f, -0.3f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = WHITE;
	ball.acceleration = { 0.0f, -9.8f, 0.0f };
	ball.velocity = { 0.0f, 0.0f, 0.0f };

	// ---------------------------------------------------------------
	// ↓ 
	// ---------------------------------------------------------------

	Plane plane{};
	plane.normal = Normalize({ -0.2f, 0.9f, -0.3f });
	plane.distance = 0.0f;

	float deltaTime = 1.0f / 60.0f;
	float e = 0.8f;

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

		// ------------------------ ボールの更新 ------------------------ //
		ball.velocity += ball.acceleration * deltaTime;
		ball.pos += ball.velocity * deltaTime;

		// ------------------------ 反射させる ------------------------ //

		if (IsCollision(Sphere(ball.pos, ball.radius), plane)) {
			Vec3f reflected = Reflect(ball.velocity, plane.normal);
			Vec3f projectToNormal = Project(reflected, plane.normal);
			Vec3f movingDire = reflected - projectToNormal;
			ball.velocity = projectToNormal * e + movingDire;
		}

		// 画面外に消えたら
		if (ball.pos.y <= -1.5f) {
			ball.pos = { 0.8f, 1.2f, -0.3f };
			ball.acceleration = { 0.0f, -9.8f, 0.0f };
			ball.velocity = { 0.0f, 0.0f, 0.0f };
		}
	
		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		DrawPlane(plane, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), WHITE);

		ball.Draw(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());
		
		ImGui::Begin("Set");

		if (ImGui::TreeNode("point")) {	
			if (ImGui::Button("Reset")) {
				ball.pos = { 0.8f, 1.2f, -0.3f };
				ball.acceleration = { 0.0f, -9.8f, 0.0f };
				ball.velocity = { 0.0f, 0.0f, 0.0f };
			}

			ImGui::DragFloat("coefficient", &e, 0.01f, 0.0f, 1.0f);
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
