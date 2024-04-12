#include "DrawUtils.h"

void DrawGrid(const Matrix4x4& viewPrijectionMatrix, const Matrix4x4& viewMatrix) {
	const float kGridHalfwidth_ = 2.0f;
	const uint32_t kSubdivision_ = 10;
	const float kGridEvery_ = (kGridHalfwidth_ * 2.0f) / float(kSubdivision_);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision_; ++xIndex) {
		float half = float(kSubdivision_) / kGridHalfwidth_;

		Vector3 stPos = { -1 , 0, float((xIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) };
		Vector3 endPos = { 1 , 0, float((xIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) };

		Matrix4x4 stWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, stPos);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, endPos);

		Matrix4x4 stWvpMatrix = Multiply(stWorldMatrix, viewPrijectionMatrix);
		Matrix4x4 endWvpMatrix = Multiply(endWorldMatrix, viewPrijectionMatrix);

		Vector3 ndcSt = Transform(stPos, stWvpMatrix);
		Vector3 ndcEnd = Transform(endPos, endWvpMatrix);

		Vector3 screenSt = Transform(ndcSt, viewMatrix);
		Vector3 screenEnd = Transform(ndcEnd, viewMatrix);

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

		Vector3 stPos = { float((zIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) , 0,1 };
		Vector3 endPos = { float((zIndex)-half) * kGridEvery_ / (float(kGridHalfwidth_)) , 0, -1 };

		Matrix4x4 stWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, stPos);
		Matrix4x4 endWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, endPos);

		Matrix4x4 stWvpMatrix = Multiply(stWorldMatrix, viewPrijectionMatrix);
		Matrix4x4 endWvpMatrix = Multiply(endWorldMatrix, viewPrijectionMatrix);

		Vector3 ndcSt = Transform(stPos, stWvpMatrix);
		Vector3 ndcEnd = Transform(endPos, endWvpMatrix);

		Vector3 screenSt = Transform(ndcSt, viewMatrix);
		Vector3 screenEnd = Transform(ndcEnd, viewMatrix);

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

			Vector3 a, b, c;
			a = { std::cos(lat) * cos(lon) * (sphere.radius / 2),
				std::sin(lat) * (sphere.radius / 2),
				std::cos(lat) * std::sin(lon) * (sphere.radius / 2) };

			b = { std::cos(lat + kLatEvery) * std::cos(lon) * (sphere.radius / 2) ,
				std::sin(lat + kLatEvery) * (sphere.radius / 2),
				std::cos(lat + kLatEvery) * std::sin(lon) * (sphere.radius / 2) };

			c = { std::cos(lat) * std::cos(lon + kLonEvery) * (sphere.radius / 2),
				std::sin(lat) * (sphere.radius / 2),
				std::cos(lat) * std::sin(lon + kLonEvery) * (sphere.radius / 2) };


			a = {
				a.x + sphere.center.x,
				a.y + sphere.center.y,
				a.z + sphere.center.z,
			};

			b = {
				b.x + sphere.center.x,
				b.y + sphere.center.y,
				b.z + sphere.center.z,
			};

			c = {
				c.x + sphere.center.x,
				c.y + sphere.center.y,
				c.z + sphere.center.z,
			};

			Matrix4x4 aWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, a);
			Matrix4x4 bWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, b);
			Matrix4x4 cWorldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, c);

			Matrix4x4 aWvpMatrix = Multiply(aWorldMatrix, viewProjectionMatrix);
			Matrix4x4 bWvpMatrix = Multiply(bWorldMatrix, viewProjectionMatrix);
			Matrix4x4 cWvpMatrix = Multiply(cWorldMatrix, viewProjectionMatrix);

			Vector3 ndcA = Transform(a, aWvpMatrix);
			Vector3 ndcB = Transform(b, bWvpMatrix);
			Vector3 ndcC = Transform(c, cWvpMatrix);

			Vector3 screenA = Transform(ndcA, viewportMatrix);
			Vector3 screenB = Transform(ndcB, viewportMatrix);
			Vector3 screenC = Transform(ndcC, viewportMatrix);

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
