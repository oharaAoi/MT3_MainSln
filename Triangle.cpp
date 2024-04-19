#include "Triangle.h"

Triangle::Triangle() { Init(); }

void Triangle::Init(){
	rotate_ = {0.0f, 0.0f, 0.0f};
	translate_ = {640.0f, 360.0f, 100.0f};

	kLocalVertex_[0] = { 0, 10.0f, 0.0f};
	kLocalVertex_[1] = { -10, -10.0f, 0.0f };
	kLocalVertex_[2] = { 10, -10.0f, 0.0f };

	screenVertex_[0] = kLocalVertex_[0];
	screenVertex_[1] = kLocalVertex_[1];
	screenVertex_[2] = kLocalVertex_[2];
}

void Triangle::Update(){
	rotate_.y += float(M_PI) / 180.0f;

	worldMatrix_ = MakeAffineMatrix({ 1.0f, 1.0f, 1.0f }, rotate_, translate_);
}

void Triangle::Draw(){

	if (dot_ < 0) {
		Novice::DrawTriangle(
			static_cast<int>(screenVertex_[0].x),
			static_cast<int>(screenVertex_[0].y),
			static_cast<int>(screenVertex_[1].x),
			static_cast<int>(screenVertex_[1].y),
			static_cast<int>(screenVertex_[2].x),
			static_cast<int>(screenVertex_[2].y),
			RED,
			kFillModeSolid
		);
	}

	VectorScreenPrintf(0, 0, cross_, "Cross");

	ImGui::Begin("tirangle");

	ImGui::SliderFloat3("rotate_", &rotate_.x, 0.0f, 1280.0f);
	ImGui::SliderFloat3("translate", &translate_.x, 0.0f, 1280.0f);
	ImGui::Text("dot:%d", dot_);

	ImGui::End();
}

void Triangle::MakeWorldViewProjectionMatrix(const Matrix4x4& viewMatrix, const Matrix4x4& projectionMatrix){
	worldViewProjectionMatrix_ = Multiply(worldMatrix_, Multiply(viewMatrix, projectionMatrix));
}

void Triangle::MakeSceenVertex(const Matrix4x4& viewportMatrix){
	for (int i = 0; i < 3; i++) {
		ndcVertex_[i] = Transform(kLocalVertex_[i], worldViewProjectionMatrix_);
		screenVertex_[i] = Transform(ndcVertex_[i], viewportMatrix);
	}
}

void Triangle::CrossToCamera(const Vec3f& cameraDire) {
	Vec3f a = screenVertex_[2] - screenVertex_[0];
	Vec3f b = screenVertex_[1] - screenVertex_[2];
	cross_ = Cross(b, a);

	dot_ = Dot(cameraDire, cross_);
}
