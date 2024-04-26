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
