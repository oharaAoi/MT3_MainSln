#include "LineCollider.h"

/// <summary>///
/// 線と平面の当たり判定
/// </summary>///
/// <param name="segment">線分</param>/// 
/// <param name="plane">平面</param>///
///  <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Segment& segment, const Plane& plane) {
	// まず内積を求める(垂直判定をする)
	float dot = Dot(plane.normal,segment.diff);

	// 垂直だったら平行で衝突しない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	// 衝突判定を取る(tが0以上1以下だったら)
	if (0 <= t && t <= 1) {
		return true;
	}

	return false;
}

/// <summary>///
/// 直線と平面の当たり判定
/// </summary>///
/// <param name="segment">直線</param>/// 
/// <param name="plane">平面</param>///
///  <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Line& line, const Plane& plane) {
	// まず内積を求める(垂直判定をする)
	float dot = Dot(plane.normal, line.diff);

	// 垂直だったら平行で衝突しない
	if (dot == 0.0f) {
		return false;
	}
	
	// tを求める
	float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	//Vec3f collisionPoint = line.origin + (line.diff * t);

	// 衝突判定を取る(tが0以上1以下だったら)
	if (0 <= t && t <= 1) {
		return true;
	}

	return false;
}

/// <summary>///
/// 半直線と平面の当たり判定
/// </summary>///
/// <param name="segment">半直線</param>/// 
/// <param name="plane">平面</param>///
///  <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Ray& ray, const Plane& plane) {
	// まず内積を求める(垂直判定をする)
	float dot = Dot(plane.normal, ray.diff);

	// 垂直だったら平行で衝突しない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (plane.distance - Dot(ray.origin, plane.normal)) / dot;

	// 衝突判定を取る(tが0以上1以下だったら)
	if (0 <= t && t <= 1) {
		return true;
	}

	return false;
}
