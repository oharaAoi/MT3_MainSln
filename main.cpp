#include <Novice.h>
#include "Matrix4x4.h"
#include "MyMath.h"
#include "DrawUtils.h"
#include "Camera.h"
#include <memory>

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

	Segment segment{ {-2.0f, -1.0f, 0.0f},{3.0f, 2.0f, 2.0f} };
	Vec3f point{ -1.5f, 0.6f, 0.6f };

	Vec3f project = Project(Subtract(point, segment.origin), segment.diff);
	Vec3f closestPoint = ClosestPoint(point, segment);

	Sphere pointShpere_{ point, 0.01f };
	Sphere closestPointShpere{ closestPoint , 0.01f };

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

		project = Project(Subtract(point, segment.origin), segment.diff);
		closestPoint = ClosestPoint(point, segment);

		pointShpere_ = { point, 0.01f };
		closestPointShpere = { closestPoint , 0.01f };

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

		DrawSphere(pointShpere_, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), RED);
		DrawSphere(closestPointShpere, camera_->GetViewProjectMatrix(), camera_->GetViewportMatrix(), BLACK);

		Novice::DrawLine(int(start.x), int(start.y), int(end.x), int(end.y), WHITE);

		ImGui::Begin("Setting");

		ImGui::DragFloat3("point", &point.x, 0.1f);
		ImGui::DragFloat3("segment.origin", &segment.origin.x, 0.1f);
		ImGui::DragFloat3("segment.diff", &segment.diff.x, 0.1f);
		ImGui::DragFloat3("project", &project.x, 0.1f);

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
