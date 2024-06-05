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

	if (std::isnan(tMin.x)) {tMin.x = 0;}
	if (std::isnan(tMin.y)) {tMin.y = 0;}
	if (std::isnan(tMin.z)) {tMin.z = 0;}

	if (std::isnan(tMax.x)) {tMax.x = 99;}
	if (std::isnan(tMax.y)) {tMax.y = 99;}
	if (std::isnan(tMax.z)) {tMax.z = 99;}

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

	Novice::ScreenPrintf(0, 0, "tmin:%f", tmin);
	Novice::ScreenPrintf(0, 10, "tmax:%f", tmax);
	VectorScreenPrintf(0, 30, tNear, "tNear");
	VectorScreenPrintf(0, 60, tFar, "tFar");
	VectorScreenPrintf(0, 90, tMin, "tMin");
	VectorScreenPrintf(0, 110, tMax, "tMax");

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
