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
	Spring spring;
	spring.anchor = { 0.0f, 1.0f, 0.0f };
	spring.naturalLength = 0.7f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	// ---------------------------------------------------------------
	// ↓ 
	// ---------------------------------------------------------------
	Ball ball{};
	ball.pos = { 0.8f, 0.2f, 0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

	float deltaTime = 1.0f / 60.0f;

	const Vec3f kGravity{ 0.0f, -9.8f, 0.0f };

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

		// ------------------------ ばねの実装 ------------------------ //
		Vec3f diff = ball.pos - spring.anchor;
		float length = Length(diff);

		if (length != 0.0f) {
			Vec3f direction = Normalize(diff);
			Vec3f restPos = spring.anchor + direction * spring.naturalLength;
			Vec3f displacement = (ball.pos - restPos) * length;
			Vec3f restoringForce = displacement * -spring.stiffness;
			// 減衰を計算
			Vec3f dampingForce = ball.velocity * -spring.dampingCoefficient;
			Vec3f force = restoringForce + dampingForce;
			ball.acceleration = force / ball.mass;
		}

		// 加速度も速度も秒基準
		ball.velocity += (ball.acceleration + kGravity) * deltaTime;
		ball.pos += (ball.velocity) * deltaTime;

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		ball.Draw(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		DrawWorldLine(spring.anchor, ball.pos, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());
		
		ImGui::Begin("Set");

		if (ImGui::Button("Start")) {
			ball.pos = { 0.8f, 0.2f, 0.0f };
		}

		if (ImGui::TreeNode("point")) {	
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
