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

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
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

			Novice::DrawLine(
				static_cast<int>(screenA.x),
				static_cast<int>(screenA.y),
				static_cast<int>(screenB.x),
				static_cast<int>(screenB.y),
				sphere.color
			);

			Novice::DrawLine(
				static_cast<int>(screenA.x),
				static_cast<int>(screenA.y),
				static_cast<int>(screenC.x),
				static_cast<int>(screenC.y),
				sphere.color
			);
		}
	}
}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color) {
	// 中心点を決める
	Vec3f center = plane.normal * plane.distance;
	Vec3f perpendiculars[4];
	// 法線と垂直なベクトルを求める
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	// 上の逆ベクトルを求める
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	// 垂直なベクトルと法線のクロス積を求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	// 上の逆ベクトルを求める
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };
	// 4つのベクトルを中心点にそれぞれ定数倍して足す
	Vec3f points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vec3f extend = perpendiculars[index] * 2.0f;
		Vec3f point = center + extend;
		points[index] = Transform(Transform(point, viewProjection), viewportMatrix);
	}

	// 線を描画する
	Novice::DrawLine(
		static_cast<int>(points[0].x),
		static_cast<int>(points[0].y),
		static_cast<int>(points[2].x),
		static_cast<int>(points[2].y),
		color);
	Novice::DrawLine(
		static_cast<int>(points[1].x),
		static_cast<int>(points[1].y),
		static_cast<int>(points[2].x),
		static_cast<int>(points[2].y),
		0xff0000ff);
	Novice::DrawLine(
		static_cast<int>(points[1].x),
		static_cast<int>(points[1].y),
		static_cast<int>(points[3].x),
		static_cast<int>(points[3].y),
		0x00ff00ff);
	Novice::DrawLine(
		static_cast<int>(points[3].x),
		static_cast<int>(points[3].y),
		static_cast<int>(points[0].x),
		static_cast<int>(points[0].y),
		0x0000ffff);
}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color, const bool& isWier) {
	// 重心を求める
	Vec3f centroid = {
		((triangle.vertices[0].x + triangle.vertices[1].x + triangle.vertices[2].x) / 3),
		((triangle.vertices[0].y + triangle.vertices[1].y + triangle.vertices[2].y) / 3),
		0 
	};

	centroid = {0,0,0};

	// ワールド行列を求める
	Matrix4x4 worldMat = MakeAffineMatrix({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, centroid);

	// 正射影行列を求める
	Matrix4x4 vpvMat = Multiply(worldMat, viewProjection) * viewportMatrix;

	// スクリーンの頂点を求める
	Vec3f screenVer[3];
	for (uint32_t index = 0; index < 3; index++) {
		screenVer[index] = Transform(triangle.vertices[index], vpvMat);
	}

	Novice::DrawTriangle(
		static_cast<int>(screenVer[0].x),
		static_cast<int>(screenVer[0].y),
		static_cast<int>(screenVer[1].x),
		static_cast<int>(screenVer[1].y),
		static_cast<int>(screenVer[2].x),
		static_cast<int>(screenVer[2].y),
		color,
		isWier ? kFillModeWireFrame : kFillModeSolid
	);
}

/// <summary>
/// AABB(軸平行境界箱)
/// </summary>
/// <param name="aabb">AABB(軸平行境界箱)</param>
/// <param name="viewProjection">正射影行列</param>
/// <param name="viewportMatrix">ビューポート行列</param>
/// <param name="color">色</param>
void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color) {
	// ワールド行列を求める
	Matrix4x4 worldMat = MakeAffineMatrix({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, { 0,0,0 });

	// 正射影行列を求める
	Matrix4x4 vpvMat = Multiply(worldMat, viewProjection) * viewportMatrix;

	// ローカルの頂点を求める
	Vec3f localVertex[8];
	// 手前の面
	localVertex[0] = aabb.min;
	localVertex[1] = {aabb.min.x, aabb.max.y, aabb.min.z};
	localVertex[2] = {aabb.max.x, aabb.max.y , aabb.min.z};
	localVertex[3] = {aabb.max.x, aabb.min.y , aabb.min.z};
	// 奥の面
	localVertex[4] = { aabb.min.x, aabb.min.y, aabb.max.z };
	localVertex[5] = { aabb.min.x, aabb.max.y, aabb.max.z };
	localVertex[6] = { aabb.max.x, aabb.min.y, aabb.max.z };
	localVertex[7] = aabb.max;

	// スクリーンの頂点を求める
	Vec3f screenVertex[8];
	for (size_t index = 0; index < 8; index++) {
		screenVertex[index] = Transform(localVertex[index], vpvMat);
	}

	// 描画
	Novice::DrawLine(static_cast<int>(screenVertex[0].x),static_cast<int>(screenVertex[0].y),static_cast<int>(screenVertex[1].x),static_cast<int>(screenVertex[1].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[0].x),static_cast<int>(screenVertex[0].y),static_cast<int>(screenVertex[3].x),static_cast<int>(screenVertex[3].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[0].x),static_cast<int>(screenVertex[0].y),static_cast<int>(screenVertex[4].x),static_cast<int>(screenVertex[4].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[1].x),static_cast<int>(screenVertex[1].y),static_cast<int>(screenVertex[2].x),static_cast<int>(screenVertex[2].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[1].x),static_cast<int>(screenVertex[1].y),static_cast<int>(screenVertex[5].x),static_cast<int>(screenVertex[5].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[2].x),static_cast<int>(screenVertex[2].y),static_cast<int>(screenVertex[3].x),static_cast<int>(screenVertex[3].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[2].x),static_cast<int>(screenVertex[2].y),static_cast<int>(screenVertex[7].x),static_cast<int>(screenVertex[7].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[3].x),static_cast<int>(screenVertex[3].y),static_cast<int>(screenVertex[6].x),static_cast<int>(screenVertex[6].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[4].x),static_cast<int>(screenVertex[4].y),static_cast<int>(screenVertex[5].x),static_cast<int>(screenVertex[5].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[4].x),static_cast<int>(screenVertex[4].y),static_cast<int>(screenVertex[6].x),static_cast<int>(screenVertex[6].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[5].x),static_cast<int>(screenVertex[5].y),static_cast<int>(screenVertex[7].x),static_cast<int>(screenVertex[7].y),color);
	Novice::DrawLine(static_cast<int>(screenVertex[6].x),static_cast<int>(screenVertex[6].y),static_cast<int>(screenVertex[7].x),static_cast<int>(screenVertex[7].y),color);
}

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjection, const Matrix4x4& viewportMatrix, const uint32_t& color) {
	// 回転行列を作成する
	Matrix4x4 rotateMatrix = obb.matRotate;
	// 平行移動分を作成
	Matrix4x4 matTranslate = MakeTranslateMatrix(obb.center);
	// 拡縮分
	Matrix4x4 matScale = MakeScaleMatrix({ 1.0f,1.0f, 1.0f });

	// ワールド行列を求める
	Matrix4x4 worldMat = matScale * rotateMatrix * matTranslate;

	// 正射影行列を求める
	Matrix4x4 vpvMat = Multiply(worldMat, viewProjection) * viewportMatrix;

	// ローカルの頂点を求める
	Vec3f localVertex[8];
	Vec3f min = obb.size * -1;
	Vec3f max = obb.size;
	// 手前の面
	localVertex[0] = min;
	localVertex[1] = { min.x, max.y, min.z };
	localVertex[2] = { max.x, max.y , min.z };
	localVertex[3] = { max.x, min.y , min.z };
	// 奥の面
	localVertex[4] = { min.x, min.y, max.z };
	localVertex[5] = { min.x, max.y, max.z };
	localVertex[6] = { max.x, min.y, max.z };
	localVertex[7] = max;

	// スクリーンの頂点を求める
	Vec3f screenVertex[8];
	for (size_t index = 0; index < 8; index++) {
		screenVertex[index] = Transform(localVertex[index], vpvMat);
	}

	// 描画
	Novice::DrawLine(static_cast<int>(screenVertex[0].x), static_cast<int>(screenVertex[0].y), static_cast<int>(screenVertex[1].x), static_cast<int>(screenVertex[1].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[0].x), static_cast<int>(screenVertex[0].y), static_cast<int>(screenVertex[3].x), static_cast<int>(screenVertex[3].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[0].x), static_cast<int>(screenVertex[0].y), static_cast<int>(screenVertex[4].x), static_cast<int>(screenVertex[4].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[1].x), static_cast<int>(screenVertex[1].y), static_cast<int>(screenVertex[2].x), static_cast<int>(screenVertex[2].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[1].x), static_cast<int>(screenVertex[1].y), static_cast<int>(screenVertex[5].x), static_cast<int>(screenVertex[5].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[2].x), static_cast<int>(screenVertex[2].y), static_cast<int>(screenVertex[3].x), static_cast<int>(screenVertex[3].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[2].x), static_cast<int>(screenVertex[2].y), static_cast<int>(screenVertex[7].x), static_cast<int>(screenVertex[7].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[3].x), static_cast<int>(screenVertex[3].y), static_cast<int>(screenVertex[6].x), static_cast<int>(screenVertex[6].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[4].x), static_cast<int>(screenVertex[4].y), static_cast<int>(screenVertex[5].x), static_cast<int>(screenVertex[5].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[4].x), static_cast<int>(screenVertex[4].y), static_cast<int>(screenVertex[6].x), static_cast<int>(screenVertex[6].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[5].x), static_cast<int>(screenVertex[5].y), static_cast<int>(screenVertex[7].x), static_cast<int>(screenVertex[7].y), color);
	Novice::DrawLine(static_cast<int>(screenVertex[6].x), static_cast<int>(screenVertex[6].y), static_cast<int>(screenVertex[7].x), static_cast<int>(screenVertex[7].y), color);
}

//void DrawBezier(const std::vector<Vec3f>& controlPoint, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, const uint32_t& color) {
//	for (uint32_t oi = 0; oi < 30 - 1; oi++) {
//		float t = static_cast<float>(oi) / 30;
//		float t2 = static_cast<float>(oi + 1) / 30;
//
//		Vec3f start = Bezier(controlPoint, t);
//		Vec3f start = Bezier(controlPoint, t);
//	}
//}

void DrawBezier(const Vec3f& control0, const Vec3f& control1, const Vec3f& control2, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, const uint32_t& color) {
	const int division = 30;
	for (uint32_t oi = 0; oi < division ; oi++) {
		float t = (float)oi / division;
		float t2 = ((float)oi + 1) / division;

		// 制御点p0,p1の補完
		Vec3f p0p1 = Lerp(control0, control1, t);
		// 制御点p1,p2の補完
		Vec3f p1p2 = Lerp(control1, control2, t);
		// さらに補完
		Vec3f p = Lerp(p0p1, p1p2, t);

		// 制御点p0,p1の補完
		p0p1 = Lerp(control0, control1, t2);
		// 制御点p1,p2の補完
		p1p2 = Lerp(control1, control2, t2);
		// さらに補完
		Vec3f p2 = Lerp(p0p1, p1p2, t2);

		// 描画する
		Matrix4x4 matWorld = MakeAffineMatrix({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, p);
		Matrix4x4 matWorld2 = MakeAffineMatrix({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, p2);

		// 正射影行列を求める
		Matrix4x4 vpvMat = Multiply(matWorld, viewProjectionMat) * viewportMat;
		Matrix4x4 vpvMat2 = Multiply(matWorld2, viewProjectionMat) * viewportMat;

		// スクリーンの点を求める
		Vec3f screenPos = Transform({ 0,0,0 }, vpvMat);
		Vec3f screenPos2 = Transform({ 0,0,0 }, vpvMat2);

		// 線を引く
		Novice::DrawLine(
			static_cast<int>(screenPos.x),
			static_cast<int>(screenPos.y),
			static_cast<int>(screenPos2.x),
			static_cast<int>(screenPos2.y),
			color
		);
	}
}

void DrawCatmullRom(const Vec3f& control0, const Vec3f& control1, const Vec3f& control2, const Vec3f& control3, const Matrix4x4& viewProjectionMat, const Matrix4x4& viewportMat, const uint32_t& color) {
	const int division = 30;
	for (uint32_t oi = 0; oi < division; oi++) {
		float t = (float)oi / division;
		float t2 = ((float)oi + 1) / division;

		Vec3f term1 = ((control0 * -1) + (control1 * 3) - (control2 * 3) + control3) * std::powf(t, 3);
		Vec3f term2 = ((control0 * 2) - (control1 * 5) + (control2 * 4) - control3) * std::powf(t, 2);
		Vec3f term3 = ((control0 * -1) + control2) * t;
		Vec3f term4 = control1 * 2;

		Vec3f point = (term1 + term2 + term3 + term4) * 0.5f;

		term1 = ((control0 * -1) + (control1 * 3) - (control2 * 3) + control3) * std::powf(t2, 3);
		term2 = ((control0 * 2) - (control1 * 5) + (control2 * 4) - control3) * std::powf(t2, 2);
		term3 = ((control0 * -1) + control2) * t2;
		term4 = control1 * 2;

		Vec3f point2 = (term1 + term2 + term3 + term4) * 0.5f;

		// 描画する
		Matrix4x4 matWorld = MakeAffineMatrix({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, point);
		Matrix4x4 matWorld2 = MakeAffineMatrix({ 1.0f,1.0f, 1.0f }, { 0,0,0 }, point2);

		// 正射影行列を求める
		Matrix4x4 vpvMat = Multiply(matWorld, viewProjectionMat) * viewportMat;
		Matrix4x4 vpvMat2 = Multiply(matWorld2, viewProjectionMat) * viewportMat;

		// スクリーンの点を求める
		Vec3f screenPos = Transform({ 0,0,0 }, vpvMat);
		Vec3f screenPos2 = Transform({ 0,0,0 }, vpvMat2);

		// 線を引く
		Novice::DrawLine(
			static_cast<int>(screenPos.x),
			static_cast<int>(screenPos.y),
			static_cast<int>(screenPos2.x),
			static_cast<int>(screenPos2.y),
			color
		);
	}
}

// 表示
void VectorScreenPrintf(int x, int y, const Vec3f& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColWidth * 3, y, "%s", label);
}

void OBB::MakeOBBAxis(const Vec3f& rotate) {
	Matrix4x4 rotateMatrix = Multiply(MakeRotateXMatrix(rotate.x), Multiply(MakeRotateYMatrix(rotate.y), MakeRotateZMatrix(rotate.z)));

	// 回転行列から軸を抽出
	orientations[0].x = rotateMatrix.m[0][0];
	orientations[0].y = rotateMatrix.m[0][1];
	orientations[0].z = rotateMatrix.m[0][2];

	orientations[1].x = rotateMatrix.m[1][0];
	orientations[1].y = rotateMatrix.m[1][1];
	orientations[1].z = rotateMatrix.m[1][2];

	orientations[2].x = rotateMatrix.m[2][0];
	orientations[2].y = rotateMatrix.m[2][1];
	orientations[2].z = rotateMatrix.m[2][2];

	matRotate = rotateMatrix;
}

std::vector<Vec3f> OBB::MakeIndex() const {
	std::vector<Vec3f> vertices;
	for (uint8_t x = 0; x < 2; ++x) {
		for (uint8_t y = 0; y < 2; ++y) {
			for (uint8_t z = 0; z < 2; ++z) {
				Vec3f localVertex = {
					(x ? size.x : -size.x),
					(y ? size.y : -size.y),
					(z ? size.z : -size.z),
				};

				Vec3f worldVertex = Transform(localVertex, matRotate);
				vertices.push_back(worldVertex + center);
			}
		}
	}

	return vertices;
}

