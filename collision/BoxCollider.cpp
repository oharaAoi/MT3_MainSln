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
