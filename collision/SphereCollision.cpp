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
