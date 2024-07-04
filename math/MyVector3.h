#pragma once

template <typename T>
class MyVector3 {

public:
	T x, y, z;

	/// <summary>
	/// 加算(vec3+vec3)
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	MyVector3 operator+(const MyVector3& obj) const {
		return MyVector3(x + obj.x, y + obj.y, z + obj.z);
	}

	/// <summary>
	/// 加算(vec3+float)
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	MyVector3 operator+(const float& obj) const {
		return MyVector3(x + obj, y + obj, z + obj);
	}

	MyVector3 operator+=(const MyVector3& obj) {
		x += obj.x;
		y += obj.y;
		z += obj.z;
		return *this;
	}

	MyVector3 operator+=(const float& obj) {
		x += obj;
		y += obj;
		z += obj;
		return *this;
	}

	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	MyVector3 operator-(const MyVector3& obj) const {
		return MyVector3(x - obj.x, y - obj.y, z - obj.z);
	}

	MyVector3 operator-(const float& obj) const {
		return MyVector3(x - obj, y - obj, z - obj);
	}

	MyVector3 operator-=(const MyVector3& obj) {
		x -= obj.x;
		y -= obj.y;
		z -= obj.z;
		return *this;
	}

	MyVector3 operator-=(const float& obj) {
		x -= obj;
		y -= obj;
		z -= obj;
		return *this;
	}

	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	MyVector3 operator*(const MyVector3& obj) const {
		return MyVector3(x * obj.x, y * obj.y, z * obj.z);
	}

	MyVector3 operator*(const float& obj) const {
		return MyVector3(x * obj, y * obj, z * obj);
	}

	MyVector3 operator*=(const MyVector3& obj) {
		x *= obj.x;
		y *= obj.y;
		z *= obj.z;
		return *this;
	}

	MyVector3 operator*=(const float& obj) {
		x *= obj;
		y *= obj;
		z *= obj;
		return *this;
	}

	/// <summary>
	/// 除算
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	MyVector3 operator/(const MyVector3& obj) const {
		return MyVector3(x / obj.x, y / obj.y, z / obj.z);
	}

	MyVector3 operator/(const float& obj) const {
		return MyVector3(x / obj, y / obj, z / obj);
	}

	MyVector3 operator/=(const MyVector3& obj) {
		x /= obj.x;
		y /= obj.y;
		z /= obj.z;
		return *this;
	}

	MyVector3 operator/=(const float& obj) {
		x /= obj;
		y /= obj;
		z /= obj;
		return *this;
	}
};

using Vec3f = MyVector3<float>;
using Vec3 = MyVector3<int>;