#include "LineCollider.h"

/// <summary>///
/// 線と平面の当たり判定
/// </summary>///
/// <param name="segment">線分</param>/// 
/// <param name="plane">平面</param>///
///  <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Segment& segment, const Plane& plane) {
	// 線分が平面の中にあるか
	Triangle triangle1 = {
		plane.vertices[2],
		plane.vertices[1],
		plane.vertices[3],
	};

	Triangle triangle2 = {
		plane.vertices[2],
		plane.vertices[3],
		plane.vertices[0],
	};

	if (!IsCollision(triangle1, segment) && !IsCollision(triangle2, segment)) {
		return false;
	}

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
	// 線分が平面の中にあるか
	Triangle triangle1 = {
		plane.vertices[2],
		plane.vertices[1],
		plane.vertices[3],
	};

	Triangle triangle2 = {
		plane.vertices[2],
		plane.vertices[3],
		plane.vertices[0],
	};

	if (!IsCollision(triangle1, line) && !IsCollision(triangle2, line)) {
		return false;
	}
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
	// 線分が平面の中にあるか
	Triangle triangle1 = {
		plane.vertices[2],
		plane.vertices[1],
		plane.vertices[3],
	};

	Triangle triangle2 = {
		plane.vertices[2],
		plane.vertices[3],
		plane.vertices[0],
	};

	if (!IsCollision(triangle1, ray) && !IsCollision(triangle2, ray)) {
		return false;
	}
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


/// <summary>///
/// 三角形と線の当たり判定
/// </summary>///
/// <param name="triangle">三角形</param>/// 
/// <param name="segment">線分</param>///
/// <returns>true: 当たっている false: 当たっていない</returns>
bool IsCollision(const Triangle& triangle, const Segment& segment) {
	// ---------------- 三角形と線分が平行かどうかを判断する ---------------- //
	// 三角形のクロス積をとる
	Vec3f vec0to2 = triangle.vertices[1] - triangle.vertices[0];
	Vec3f vec2to1 = triangle.vertices[2] - triangle.vertices[1];
	// 法線を求める
	Vec3f cross = Cross(vec0to2, vec2to1);
	Vec3f normalizeCross = Normalize(cross);
	// 距離を求める
	float distance = Distance(triangle.vertices[0], normalizeCross);

	// まず内積を求める(垂直判定をする)
	float dot = Dot(cross, segment.diff);

	// 垂直だったら平行で衝突しない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (distance - Dot(segment.origin, cross)) / dot;

	//// 衝突判定を取る(tが0以上1以下だったら)
	//if (0 <= t && t <= 1) {

	//} else {
	//	return false;
	//}

	// ---------------- 衝突点が三角形の内側かどうか ---------------- //
	// 平面の衝突点を求める
	Vec3f p = segment.origin + (segment.diff * t);

	// 各辺を結んだベクトルと頂点と衝突点pを結んだベクトルのクロス積をとる
	Vec3f cross01 = Cross({ triangle.vertices[1] - triangle.vertices[0] }, { p - triangle.vertices[1] });
	Vec3f cross12 = Cross({ triangle.vertices[2] - triangle.vertices[1] }, { p - triangle.vertices[2] });
	Vec3f cross20 = Cross({ triangle.vertices[0] - triangle.vertices[2] }, { p - triangle.vertices[0] });

	// すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Dot(cross01, normalizeCross) >= 0.0f &&
		Dot(cross12, normalizeCross) >= 0.0f &&
		Dot(cross20, normalizeCross) >= 0.0f) {

		return true;
	}

	return false;
}

bool IsCollision(const Triangle& triangle, const Ray& ray) {
	// ---------------- 三角形と線分が平行かどうかを判断する ---------------- //
	// 三角形のクロス積をとる
	Vec3f vec0to2 = triangle.vertices[1] - triangle.vertices[0];
	Vec3f vec2to1 = triangle.vertices[2] - triangle.vertices[1];
	// 法線を求める
	Vec3f cross = Cross(vec0to2, vec2to1);
	Vec3f normalizeCross = Normalize(cross);
	// 距離を求める
	float distance = Distance(triangle.vertices[0], normalizeCross);

	// まず内積を求める(垂直判定をする)
	float dot = Dot(cross, ray.diff);

	// 垂直だったら平行で衝突しない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (distance - Dot(ray.origin, cross)) / dot;

	//// 衝突判定を取る(tが0以上1以下だったら)
	//if (0 <= t && t <= 1) {

	//} else {
	//	return false;
	//}

	// ---------------- 衝突点が三角形の内側かどうか ---------------- //
	// 平面の衝突点を求める
	Vec3f p = ray.origin + (ray.diff * t);

	// 各辺を結んだベクトルと頂点と衝突点pを結んだベクトルのクロス積をとる
	Vec3f cross01 = Cross({ triangle.vertices[1] - triangle.vertices[0] }, { p - triangle.vertices[1] });
	Vec3f cross12 = Cross({ triangle.vertices[2] - triangle.vertices[1] }, { p - triangle.vertices[2] });
	Vec3f cross20 = Cross({ triangle.vertices[0] - triangle.vertices[2] }, { p - triangle.vertices[0] });

	// すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Dot(cross01, normalizeCross) >= 0.0f &&
		Dot(cross12, normalizeCross) >= 0.0f &&
		Dot(cross20, normalizeCross) >= 0.0f) {

		return true;
	}

	return false;
}

bool IsCollision(const Triangle& triangle, const Line& line) {
	// ---------------- 三角形と線分が平行かどうかを判断する ---------------- //
	// 三角形のクロス積をとる
	Vec3f vec0to2 = triangle.vertices[1] - triangle.vertices[0];
	Vec3f vec2to1 = triangle.vertices[2] - triangle.vertices[1];
	// 法線を求める
	Vec3f cross = Cross(vec0to2, vec2to1);
	Vec3f normalizeCross = Normalize(cross);
	// 距離を求める
	float distance = Distance(triangle.vertices[0], normalizeCross);

	// まず内積を求める(垂直判定をする)
	float dot = Dot(cross, line.diff);

	// 垂直だったら平行で衝突しない
	if (dot == 0.0f) {
		return false;
	}

	// tを求める
	float t = (distance - Dot(line.origin, cross)) / dot;

	//// 衝突判定を取る(tが0以上1以下だったら)
	//if (0 <= t && t <= 1) {

	//} else {
	//	return false;
	//}

	// ---------------- 衝突点が三角形の内側かどうか ---------------- //
	// 平面の衝突点を求める
	Vec3f p = line.origin + (line.diff * t);

	// 各辺を結んだベクトルと頂点と衝突点pを結んだベクトルのクロス積をとる
	Vec3f cross01 = Cross({ triangle.vertices[1] - triangle.vertices[0] }, { p - triangle.vertices[1] });
	Vec3f cross12 = Cross({ triangle.vertices[2] - triangle.vertices[1] }, { p - triangle.vertices[2] });
	Vec3f cross20 = Cross({ triangle.vertices[0] - triangle.vertices[2] }, { p - triangle.vertices[0] });

	// すべての小三角形のクロス積と法線が同じ方向を向いていたら衝突
	if (Dot(cross01, normalizeCross) >= 0.0f &&
		Dot(cross12, normalizeCross) >= 0.0f &&
		Dot(cross20, normalizeCross) >= 0.0f) {

		return true;
	}

	return false;
}
