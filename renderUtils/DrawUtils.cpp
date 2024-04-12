#include "DrawUtils.h"

void DrawGrid(const Matrix4x4& viewPrijectionMatrix, const Matrix4x4& viewMatrix) {
	const float kGridHalfwidth_ = 2.0f;
	const uint32_t kSubdivision_ = 10;
	const float kGridEvery_ = (kGridHalfwidth_ * 2.0f) / float(kSubdivision_);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision_; ++xIndex) {
		float half = float(kSubdivision_) / kGridHalfwidth_;

		Vec3f stPos = { -1 , 0, float((xIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) };
		Vec3f endPos = { 1 , 0, float((xIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) };

		Matrix4x4 stWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, stPos);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, endPos);

		Matrix4x4 stWvpMatrix = Multiply(stWorldMatrix, viewPrijectionMatrix);
		Matrix4x4 endWvpMatrix = Multiply(endWorldMatrix, viewPrijectionMatrix);

		Vec3f ndcSt = Transform(stPos, stWvpMatrix);
		Vec3f ndcEnd = Transform(endPos, endWvpMatrix);

		Vec3f screenSt = Transform(ndcSt, viewMatrix);
		Vec3f screenEnd = Transform(ndcEnd, viewMatrix);

		if (xIndex == 5) {
			Novice::DrawLine(
				static_cast<int>(screenSt.x),
				static_cast<int>(screenSt.y),
				static_cast<int>(screenEnd.x),
				static_cast<int>(screenEnd.y),
				0x000000ff
			);
		} else {
			Novice::DrawLine(
				static_cast<int>(screenSt.x),
				static_cast<int>(screenSt.y),
				static_cast<int>(screenEnd.x),
				static_cast<int>(screenEnd.y),
				0xaaaaaaff
			);
		}
	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision_; ++zIndex) {
		float half = float(kSubdivision_) / kGridHalfwidth_;

		Vec3f stPos = { float((zIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) , 0,1 };
		Vec3f endPos = { float((zIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) , 0, -1 };

		Matrix4x4 stWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, stPos);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, endPos);

		Matrix4x4 stWvpMatrix = Multiply(stWorldMatrix, viewPrijectionMatrix);
		Matrix4x4 endWvpMatrix = Multiply(endWorldMatrix, viewPrijectionMatrix);

		Vec3f ndcSt = Transform(stPos, stWvpMatrix);
		Vec3f ndcEnd = Transform(endPos, endWvpMatrix);

		Vec3f screenSt = Transform(ndcSt, viewMatrix);
		Vec3f screenEnd = Transform(ndcEnd, viewMatrix);

		if (zIndex == 5) {
			Novice::DrawLine(
				static_cast<int>(screenSt.x),
				static_cast<int>(screenSt.y),
				static_cast<int>(screenEnd.x),
				static_cast<int>(screenEnd.y),
				0x000000ff
			);
		} else {
			Novice::DrawLine(
				static_cast<int>(screenSt.x),
				static_cast<int>(screenSt.y),
				static_cast<int>(screenEnd.x),
				static_cast<int>(screenEnd.y),
				0xaaaaaaff
			);
		}
	}

}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 16;
	const float kLonEvery = 2.0f * float(M_PI) / kSubdivision;
	const float kLatEvery = float(M_PI) / kSubdivision;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -float(M_PI) / 2.0f + kLatEvery * latIndex; // 現在の緯度 theta

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery; // 現在の経度 fai

			Vec3f a, b, c;
			Vec3f localA{}, localB{}, localC{};
			localA = {
				std::cos(lat) * cos(lon) * (sphere.radius / 2),
				std::sin(lat) * (sphere.radius / 2),
				std::cos(lat) * std::sin(lon) * (sphere.radius / 2)
			};

			localB = {
				std::cos(lat + kLatEvery) * std::cos(lon) * (sphere.radius / 2) ,
				std::sin(lat + kLatEvery) * (sphere.radius / 2),
				std::cos(lat + kLatEvery) * std::sin(lon) * (sphere.radius / 2)
			};

			localC = {
				std::cos(lat) * std::cos(lon + kLonEvery) * (sphere.radius / 2),
				std::sin(lat) * (sphere.radius / 2),
				std::cos(lat) * std::sin(lon + kLonEvery) * (sphere.radius / 2)
			};


			a = {
				localA.x + sphere.center.x,
				localA.y + sphere.center.y,
				localA.z + sphere.center.z,
			};

			b = {
				localB.x + sphere.center.x,
				localB.y + sphere.center.y,
				localB.z + sphere.center.z,
			};

			c = {
				localC.x + sphere.center.x,
				localC.y + sphere.center.y,
				localC.z + sphere.center.z,
			};

			Matrix4x4 aWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, a);
			Matrix4x4 bWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, b);
			Matrix4x4 cWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, c);

			Matrix4x4 aWvpMatrix = Multiply(aWorldMatrix, viewProjectionMatrix);
			Matrix4x4 bWvpMatrix = Multiply(bWorldMatrix, viewProjectionMatrix);
			Matrix4x4 cWvpMatrix = Multiply(cWorldMatrix, viewProjectionMatrix);

			Vec3f ndcA = Transform(localA, aWvpMatrix);
			Vec3f ndcB = Transform(localB, bWvpMatrix);
			Vec3f ndcC = Transform(localC, cWvpMatrix);

			Vec3f screenA = Transform(ndcA, viewportMatrix);
			Vec3f screenB = Transform(ndcB, viewportMatrix);
			Vec3f screenC = Transform(ndcC, viewportMatrix);

			if (lonIndex >= kSubdivision / 2) {
				Novice::DrawLine(
					static_cast<int>(screenA.x),
					static_cast<int>(screenA.y),
					static_cast<int>(screenB.x),
					static_cast<int>(screenB.y),
					color
				);

				Novice::DrawLine(
					static_cast<int>(screenA.x),
					static_cast<int>(screenA.y),
					static_cast<int>(screenC.x),
					static_cast<int>(screenC.y),
					color
				);
			} else {
				Novice::DrawLine(
					static_cast<int>(screenA.x),
					static_cast<int>(screenA.y),
					static_cast<int>(screenB.x),
					static_cast<int>(screenB.y),
					0xffffffff
				);

				Novice::DrawLine(
					static_cast<int>(screenA.x),
					static_cast<int>(screenA.y),
					static_cast<int>(screenC.x),
					static_cast<int>(screenC.y),
					0xffffffff
				);
			}
		}
	}
}

// 表示
void VectorScreenPrintf(int x, int y, const Vec3f& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColWidth * 3, y, "%s", label);
}