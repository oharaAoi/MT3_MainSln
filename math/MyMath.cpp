#include "MyMath.h"

Vec3f GetStartPoint(const Vec3f& startPos, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	return Transform(Transform(startPos, viewProjectionMatrix), viewportMatrix);
}

Vec3f GetEndPoint(const Vec3f& endPos, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	return Transform(Transform(endPos, viewProjectionMatrix), viewportMatrix);
}

//=================================================================================================================
//	↓　四則演算
//=================================================================================================================
/// <summary>
/// 加算
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Add(const Vec3f& v1, const Vec3f& v2) {
	Vec3f result{};

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

/// <summary>
/// 減算
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f  Subtract(const Vec3f& v1, const Vec3f& v2) {
	Vec3f result{};

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

/// <summary>
/// 掛け算
/// </summary>
/// <param name="scalar"></param>
/// <param name="v"></param>
/// <returns></returns>
Vec3f Multiply(float scalar, const Vec3f& v) {
	Vec3f result{};

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;

	return result;
}

//=================================================================================================================
//	↓	ベクトルの内積外積
//=================================================================================================================
/// <summary>
/// 内積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vec3f& v1, const Vec3f& v2) {
	float result{};

	result = (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);

	return result;
}

/// <summary>
/// クロス積
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Cross(const Vec3f& v1, const Vec3f& v2) {
	Vec3f result{};

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

//=================================================================================================================
//	↓	ベクトルの長さに関する関数
//=================================================================================================================
/// <summary>
/// ノルム
/// </summary>
/// <param name="vec3"></param>
/// <returns></returns>
float Length(const Vec3f& vec3) {
	return std::sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
}

/// <summary>
/// 正規化
/// </summary>
/// <param name="vec3"></param>
/// <returns></returns>
Vec3f Normalize(const Vec3f& vec3){
    Vec3f result = vec3;

    float len = Length(vec3);
    if (len != 0) {
        result.x /= len;
        result.y /= len;
        result.z /= len;
    }

    return result;
}

//void Normalize(Vec3f& v) {
//	float len = Length(v);
//	if (len != 0) {
//		v.x /= len;
//		v.y /= len;
//		v.z /= len;
//	}
//}

/// <summary>
/// 正射影ベクトル
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Project(const Vec3f& v1, const Vec3f& v2) {
	Vec3f result{};
	float middle{};
	Vec3f unitVector = Normalize(v2);

	middle = Dot(v1, unitVector);

	result = unitVector * middle;

	return result;
}

/// <summary>
/// 垂直なベクトルを返す関数
/// </summary>
/// <param name="vector">法線</param>
/// <returns>垂直ベクトル</returns>
Vec3f Perpendicular(const Vec3f& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y, vector.x, 0.0f };
	}
	return { 0.0f, -vector.z, vector.y };
}

/// <summary>
/// 最近接点を求める関数
/// </summary>
/// <param name="point">点P(ここから線分へのベクトルをベクトル射影する)</param>
/// <param name="segment"></param>
/// <returns></returns>
Vec3f ClosestPoint(const Vec3f& point, const Segment& segment) {
	Vec3f result{};
	// 正射影ベクトルを求める
	Vec3f projVector = Project(Subtract(point, segment.origin), segment.diff);
	// 最近接点を求める
	result = segment.origin + projVector;

	return result;
}

Vec3f TransformNormal(const Vec3f& v, const Matrix4x4& m) {
	Vec3f result{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};

	return result;
}

Vec3f ApplyRotation(const Vec3f& direction, const Matrix4x4& mat) {
	Vec3f result;
	result.x = mat.m[0][0] * direction.x + mat.m[0][1] * direction.y + mat.m[0][2] * direction.z;
	result.y = mat.m[1][0] * direction.x + mat.m[1][1] * direction.y + mat.m[1][2] * direction.z;
	result.z = mat.m[2][0] * direction.x + mat.m[2][1] * direction.y + mat.m[2][2] * direction.z;
	return result;
}

/// <summary>
/// 線形補完
/// </summary>
/// <param name="p1">制御点1</param>
/// <param name="p2">制御点2</param>
/// <param name="t">時間</param>
/// <returns>p1をp2までにt時間分進めた値</returns>
Vec3f Lerp(const Vec3f& p1, const Vec3f& p2, const float& t) {
	return (p2 - p1) * t + p1;
}

Vec3f Bezier(const std::vector<Vec3f>& controlPoint, const float& t) {
	if (controlPoint.size() == 1) {
		return controlPoint[0];
	}

	std::vector<Vec3f> lerpVec;
	for (size_t i = 0; i < controlPoint.size() - 1; ++i) {
		lerpVec.push_back(Lerp(controlPoint[i], controlPoint[i + 1], t));
	}

	return Bezier(lerpVec, t);
}
