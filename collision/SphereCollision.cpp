#include "SphereCollision.h"

/// <summary>///
/// 球同士の当たり判定
/// </summary>///
/// <param name="s1">球1</param>///
/// <param name="s2">球2</param>///
/// <returns></returns>
bool IsCollision(const Sphere& s1, const Sphere& s2) {
	// 中心点間の距離を求める
	float distance = Length(s1.center - s2.center);
	// 半径の合計よりも短ければ衝突
	if (distance <= s1.radius + s2.radius) {
		return true;
	}

	return false;
}

/// <summary>/// 
/// 球と平面の当たり判定
/// </summary>/// 
/// <param name="s1">球1</param>/// 
/// <param name="p1">平面1</param>/// 
/// <returns>true:当たっている　false:当たっていない</returns>
bool IsCollision(const Sphere& s1, const Plane& p1) {
	// 法線と球の中心点で平面方程式を行う
	float dot = Dot(p1.normal, s1.center);
	// 平面と球の中心点の距離を求める
	float distance = std::abs(dot - p1.distance);

	if (distance <= s1.radius) {
		return true;
	}

	return false;
}

bool IsCollisionCapsule(const Ball& ball, const Plane& p1) {
	Capsule capsule = CreateCapsule(ball);

	// カプセルの始点と平面の内積をとる
	float dot1 = Dot(capsule.segment.origin, p1.normal);
	// 終点
	float dot2 = Dot(capsule.segment.origin + capsule.segment.diff, p1.normal);

	float distance = std::abs(dot1 - p1.distance);

	Line ballLine{};
	ballLine.origin = capsule.segment.origin;
	ballLine.origin = capsule.segment.diff;

	// 線分が平面を貫通しているか
	if (!IsCollision(ballLine, p1)) {
		if (distance > ball.radius) {
			return false;
		}
	}
	
	if (dot1 > 0.0f && dot2 < 0.0f) {
		return true;
	} else if (dot1 < 0.0f && dot2 > 0.0f) {
		return true;
	}

	if (distance <= ball.radius) {
		return true;
	}


	return false;
}

Vec3f BackBall(const Ball& ball, const Plane& p1) {
	Capsule capsule = CreateCapsule(ball);
	// 始点から終点の位置
	Vec3f endPos = capsule.segment.origin + capsule.segment.diff;
	float capsuleDistance = Length(endPos - capsule.segment.origin);

	// カプセルの始点と平面の内積をとる
	float dot1 = Dot(capsule.segment.origin, p1.normal);
	// 終点
	float dot2 = Dot(endPos, p1.normal);

	// 平面と球の中心点の距離を求める
	float distance = 0;
	if (dot1 > 0.0f && dot2 < 0.0f) {
		distance = std::abs(dot1 - p1.distance);
	} else if (dot1 < 0.0f && dot2 > 0.0f) {
		distance = std::abs(dot2 - p1.distance);
	}

	//戻す方向
	Vec3f dire = Normalize(capsule.segment.origin - endPos);
	// 戻す長さ
	float backLength = (capsuleDistance - distance);

	return endPos + (dire * backLength) + (p1.normal * ball.radius);
}