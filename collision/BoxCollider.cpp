#include "BoxCollider.h"

bool IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) {
		
	} else {
		return false;
	}

	if (aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) {

	} else {
		return false;
	}

	if (aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z) {

	} else {
		return false;
	}

	return true;

}

bool IsCollision(const AABB& aabb, const Sphere& sphere) {
	// 最近傍点を求める
	Vec3f closestPoint{
		std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
		std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
		std::clamp(sphere.center.z, aabb.min.z, aabb.max.z)
	};

	// 最近傍点ト球の中心の距離を求める
	float distance = Length(closestPoint - sphere.center);

	// 距離が半径よりも小さければ衝突
	if (distance <= sphere.radius) {
		return true;
	}

	return false;
}

bool IsCollision(const AABB& aabb, const Segment& segment) {
	// 衝突点の媒介変数を求める
	Vec3f tMin = (aabb.min - segment.origin) / segment.diff;
	Vec3f tMax = (aabb.max - segment.origin) / segment.diff;

	if (std::isnan(tMin.x)) { tMin.x = 0; }
	if (std::isnan(tMin.y)) { tMin.y = 0; }
	if (std::isnan(tMin.z)) { tMin.z = 0; }

	if (std::isnan(tMax.x)) { tMax.x = 99; }
	if (std::isnan(tMax.y)) { tMax.y = 99; }
	if (std::isnan(tMax.z)) { tMax.z = 99; }

	// 衝突点の内近い方と小さい方を求める
	Vec3f tNear{
		std::min(tMin.x, tMax.x),
		std::min(tMin.y, tMax.y),
		std::min(tMin.z, tMax.z),
	};

	// 遠い方
	Vec3f tFar{
		std::max(tMin.x, tMax.x),
		std::max(tMin.y, tMax.y),
		std::max(tMin.z, tMax.z),
	};

	// 貫通している状況かを調べる
	// 近い方の大きい方を求める
	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	// 遠い方の小さい方を求める
	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax) {
		if (0 <= tmin && tmin <= 1) {
			return true;
		}

		if (0 <= tmax && tmax <= 1) {
			return true;
		}

		if (tmin <= 0 && tmax >= 1) {
			return true;
		}
	}

	return false;
}

bool IsCollision(const AABB& aabb, const Ray& ray) {
	// 衝突点の媒介変数を求める
	Vec3f tMin = (aabb.min - ray.origin) / ray.diff;
	Vec3f tMax = (aabb.max - ray.origin) / ray.diff;

	if (std::isnan(tMin.x)) { tMin.x = 0; }
	if (std::isnan(tMin.y)) { tMin.y = 0; }
	if (std::isnan(tMin.z)) { tMin.z = 0; }

	if (std::isnan(tMax.x)) { tMax.x = 99; }
	if (std::isnan(tMax.y)) { tMax.y = 99; }
	if (std::isnan(tMax.z)) { tMax.z = 99; }

	// 衝突点の内近い方と小さい方を求める
	Vec3f tNear{
		std::min(tMin.x, tMax.x),
		std::min(tMin.y, tMax.y),
		std::min(tMin.z, tMax.z),
	};

	// 遠い方
	Vec3f tFar{
		std::max(tMin.x, tMax.x),
		std::max(tMin.y, tMax.y),
		std::max(tMin.z, tMax.z),
	};

	// 貫通している状況かを調べる
	// 近い方の大きい方を求める
	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	// 遠い方の小さい方を求める
	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax) {
		if (tmin <= 1) {
			return true;
		}

		if (tmax <= 1) {
			return true;
		}

		if (tmax >= 1) {
			return true;
		}
	}

	return false;
}

bool IsCollision(const AABB& aabb, const Line& line) {
	// 衝突点の媒介変数を求める
	Vec3f tMin = (aabb.min - line.origin) / line.diff;
	Vec3f tMax = (aabb.max - line.origin) / line.diff;

	if (std::isnan(tMin.x)) { tMin.x = 0; }
	if (std::isnan(tMin.y)) { tMin.y = 0; }
	if (std::isnan(tMin.z)) { tMin.z = 0; }

	if (std::isnan(tMax.x)) { tMax.x = 99; }
	if (std::isnan(tMax.y)) { tMax.y = 99; }
	if (std::isnan(tMax.z)) { tMax.z = 99; }

	// 衝突点の内近い方と小さい方を求める
	Vec3f tNear{
		std::min(tMin.x, tMax.x),
		std::min(tMin.y, tMax.y),
		std::min(tMin.z, tMax.z),
	};

	// 遠い方
	Vec3f tFar{
		std::max(tMin.x, tMax.x),
		std::max(tMin.y, tMax.y),
		std::max(tMin.z, tMax.z),
	};

	// 貫通している状況かを調べる
	// 近い方の大きい方を求める
	float tmin = std::max(std::max(tNear.x, tNear.y), tNear.z);
	// 遠い方の小さい方を求める
	float tmax = std::min(std::min(tFar.x, tFar.y), tFar.z);

	if (tmin <= tmax) {
		return true;
	}

	return false;
}

/// <summary>/// 
/// OBBと球の当たり判定
/// </summary>///
///  <param name="obb"></param>///
/// <param name="sphere"></param>///
///  <returns></returns>
bool IsCollision(const OBB& obb, const Sphere& sphere) {
	// 回転行列を作成する
	Matrix4x4 rotateMatrix = obb.matRotate;
	// 平行移動分を作成
	Matrix4x4 matTranslate = MakeTranslateMatrix(obb.center);
	// ワールド行列を作成
	Matrix4x4 obbMatWorld = rotateMatrix * matTranslate;
	Matrix4x4 obbMatWorldInverse = Inverse(obbMatWorld);

	// 中心点を作成
	Vec3f centerInOBBLocal = Transform(sphere.center, obbMatWorldInverse);

	// OBBからABBを作成
	AABB aabbOBBLocal{ .min = obb.size * -1, .max = obb.size };
	Sphere sphereOBBLocal{ .center = centerInOBBLocal, .radius = sphere.radius, .color = sphere.color };

	// ローカル空間で衝突判定
	if (IsCollision(aabbOBBLocal, sphereOBBLocal)) {
		return true;
	}

	return false;
}

/// <summary>
/// OBBと線分の当たり判定
/// </summary>
/// <param name="obb"></param>
/// <param name="segment"></param>
/// <returns></returns>
bool IsCollision(const OBB& obb, const Segment& segment) {
	// 回転行列を作成する
	Matrix4x4 rotateMatrix = obb.matRotate;
	// 平行移動分を作成
	Matrix4x4 matTranslate = MakeTranslateMatrix(obb.center);
	// ワールド行列を作成
	Matrix4x4 obbMatWorld = rotateMatrix * matTranslate;
	// -M
	Matrix4x4 obbMatWorldInverse = Inverse(obbMatWorld);

	// 線分の始点と終点をAABBのローカル空間に変換する
	Vec3f localOrigin = Transform(segment.origin, obbMatWorldInverse);
	Vec3f localEnd = Transform(segment.origin + segment.diff, obbMatWorldInverse);

	// OBBからABBを作成
	AABB aabbOBBLocal{ .min = obb.size * -1, .max = obb.size };
	// ローカルの線分を生成
	Segment localSegment = {
		.origin = localOrigin,
		.diff = localEnd - localOrigin
	};

	// 当たり判定
	if (IsCollision(aabbOBBLocal, localSegment)) {
		return true;
	}

	return false;
}

bool IsCollision(const OBB& obb, const Ray& ray) {
	// 回転行列を作成する
	Matrix4x4 rotateMatrix = obb.matRotate;
	// 平行移動分を作成
	Matrix4x4 matTranslate = MakeTranslateMatrix(obb.center);
	// ワールド行列を作成
	Matrix4x4 obbMatWorld = rotateMatrix * matTranslate;
	// -M
	Matrix4x4 obbMatWorldInverse = Inverse(obbMatWorld);

	// 線分の始点と終点をAABBのローカル空間に変換する
	Vec3f localOrigin = Transform(ray.origin, obbMatWorldInverse);
	Vec3f localEnd = Transform(ray.origin + ray.diff, obbMatWorldInverse);

	// OBBからABBを作成
	AABB aabbOBBLocal{ .min = obb.size * -1, .max = obb.size };
	// ローカルの線分を生成
	Ray localRay = {
		.origin = localOrigin,
		.diff = localEnd - localOrigin
	};

	// 当たり判定
	if (IsCollision(aabbOBBLocal, localRay)) {
		return true;
	}

	return false;
}

bool IsCollision(const OBB& obb, const Line& line) {
	// 回転行列を作成する
	Matrix4x4 rotateMatrix = obb.matRotate;
	// 平行移動分を作成
	Matrix4x4 matTranslate = MakeTranslateMatrix(obb.center);
	// ワールド行列を作成
	Matrix4x4 obbMatWorld = rotateMatrix * matTranslate;
	// -M
	Matrix4x4 obbMatWorldInverse = Inverse(obbMatWorld);

	// 線分の始点と終点をAABBのローカル空間に変換する
	Vec3f localOrigin = Transform(line.origin, obbMatWorldInverse);
	Vec3f localEnd = Transform(line.origin + line.diff, obbMatWorldInverse);

	// OBBからABBを作成
	AABB aabbOBBLocal{ .min = obb.size * -1, .max = obb.size };
	// ローカルの線分を生成
	Line localLine = {
		.origin = localOrigin,
		.diff = localEnd - localOrigin
	};

	// 当たり判定
	if (IsCollision(aabbOBBLocal, localLine)) {
		return true;
	}
	return false;
}

//==================================================================
// OBBとOBB
//==================================================================
bool IsCollision(const OBB& obb1, const OBB& obb2) {
	// 分離軸の組み合わせを取得
	std::vector<Vec3f> crossSeparatingAxises;
	for (uint8_t obb1Index = 0; obb1Index < 3; obb1Index++) {
		for (uint8_t obb2Index = 0; obb2Index < 3; obb2Index++) {
			Vec3f crossAxis = Cross(obb1.orientations[obb1Index], obb2.orientations[obb2Index]);
			if (Length(crossAxis) > 1e-6) { // 長さが非常に小さい場合を除外
				Normalize(crossAxis);
				crossSeparatingAxises.push_back(crossAxis);
			}
		}
	}

	// 面法線をまとめる
	std::vector<Vec3f> obb1SurfaceNormals;
	for (uint8_t obbIndex = 0; obbIndex < 3; obbIndex++) {
		obb1SurfaceNormals.push_back(Normalize(TransformNormal(obb1.orientations[obbIndex], obb1.matRotate)));
	}

	std::vector<Vec3f> obb2SurfaceNormals;
	for (uint8_t obbIndex = 0; obbIndex < 3; obbIndex++) {
		obb2SurfaceNormals.push_back(Normalize(TransformNormal(obb2.orientations[obbIndex], obb2.matRotate)));
	}

	// ------------------------------------------------------------
	// 分離軸を割り出す
	std::vector<Vec3f> separatingAxises;
	separatingAxises.insert(separatingAxises.end(), obb1SurfaceNormals.begin(), obb1SurfaceNormals.end());
	separatingAxises.insert(separatingAxises.end(), obb2SurfaceNormals.begin(), obb2SurfaceNormals.end());
	separatingAxises.insert(separatingAxises.end(), crossSeparatingAxises.begin(), crossSeparatingAxises.end());

	// obbから頂点を取り出す
	std::vector<Vec3f> obb1Indecies = obb1.MakeIndex();
	std::vector<Vec3f> obb2Indecies = obb2.MakeIndex();

	// 頂点を分離軸候補に射影したベクトルを格納する

	// 取り出した頂点を分離軸へ射影する
	for (uint8_t axis = 0; axis < separatingAxises.size(); axis++) {
		std::vector<float> obb1ProjectIndecies;
		std::vector<float> obb2ProjectIndecies;

		for (uint8_t oi = 0; oi < obb1Indecies.size(); oi++) {
			// 各obbの頂点を射影する
			// 正射影ベクトルの長さを求める
			obb1ProjectIndecies.push_back(Dot(obb1Indecies[oi], separatingAxises[axis]));
			obb2ProjectIndecies.push_back(Dot(obb2Indecies[oi], separatingAxises[axis]));
		}

		// 最大値/最小値を取り出す
		float maxObb1 = *std::max_element(obb1ProjectIndecies.begin(), obb1ProjectIndecies.end());
		float maxObb2 = *std::max_element(obb2ProjectIndecies.begin(), obb2ProjectIndecies.end());
		float minObb1 = *std::min_element(obb1ProjectIndecies.begin(), obb1ProjectIndecies.end());
		float minObb2 = *std::min_element(obb2ProjectIndecies.begin(), obb2ProjectIndecies.end());

		// 影の長さを得る
		float projectLenght1 = float(maxObb1 - minObb1);
		float projectLenght2 = float(maxObb2 - minObb2);

		float sumSpan = projectLenght1 + projectLenght2;
		float longSpan = ((std::max)(maxObb1, maxObb2) - ((std::min)(minObb1, minObb2)));

		// 影の長さの合計 < 2つの影の両端の差分だったら分離軸が存在しているためfalse
		if (sumSpan <= longSpan) {
			Novice::ScreenPrintf(0, 0, "sumSpan: %f", sumSpan);
			Novice::ScreenPrintf(0, 20, "longSpan: %f", longSpan);

			return false;
		}
	}

	return true;
}
