#include "MyMath.h"

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