#include <Novice.h>
#include "Matrix4x4.h"
#include "MyMath.h"
#include "DrawUtils.h"
#include "Camera.h"
#include <memory>
#include "SphereCollision.h"
#include "LineCollider.h"

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
	// ↓ 球
	// ---------------------------------------------------------------
	Sphere sphere{};
	sphere.center = { 0.0f, 0.0f, 0.0f };
	sphere.radius = 0.5f;
	sphere.color = 0xffffffff;

	// ---------------------------------------------------------------
	// ↓ 三角形
	// ---------------------------------------------------------------
	Triangle triangle{};
	triangle.vertices[0] = Vec3f(0, 1, 0);
	triangle.vertices[1] = Vec3f(1, 0, 0);
	triangle.vertices[2] = Vec3f(-1, 0, 0);

	// ---------------------------------------------------------------
	// ↓ 線
	// ---------------------------------------------------------------
	Vec3f segmentStPoint = { -1.0f, 0.0f, 0.0f };
	Vec3f segmentEndPoint = { 1.0f, 1.0f, 1.0f };
	Segment segment{ segmentStPoint,segmentEndPoint };
	unsigned int lineColor = WHITE;

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

		segment = { segmentStPoint,segmentEndPoint };

		Vec3f start = Transform(Transform(segment.origin, camera_->GetViewProjectMatrix()), camera_->GetViewportMatrix());

		Vec3f end = Transform(
			Transform(
				Add(segment.origin, segment.diff),
				camera_->GetViewProjectMatrix()
			),
			camera_->GetViewportMatrix());

		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///

		camera_->Draw();

		DrawGrid(camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix());

		DrawTriangle(triangle, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), WHITE, true);

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), lineColor);

		ImGui::Begin("Set");
		
		if (ImGui::TreeNode("segmet")) {
			ImGui::DragFloat3("StPoint", &segmentStPoint.x, 0.01f);
			ImGui::DragFloat3("EndPoint", &segmentEndPoint.x, 0.01f);
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
