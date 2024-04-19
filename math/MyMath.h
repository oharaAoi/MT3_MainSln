#pragma once
#include "Vector2.h"
#include "MyVector3.h"
#include "Vector4.h"

#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

//=================================================================================================================
//	���@�l�����Z
//=================================================================================================================
/// <summary>
/// ���Z
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Add(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// ���Z
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f  Subtract(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// �|���Z
/// </summary>
/// <param name="scalar"></param>
/// <param name="v"></param>
/// <returns></returns>
Vec3f Multiply(float scalar, const Vec3f& v);

//=================================================================================================================
//	��	�x�N�g���̓��ϊO��
//=================================================================================================================
/// <summary>
/// ����
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
float Dot(const Vec3f& v1, const Vec3f& v2);

/// <summary>
/// �N���X��
/// </summary>
/// <param name="v1"></param>
/// <param name="v2"></param>
/// <returns></returns>
Vec3f Cross(const Vec3f& v1, const Vec3f& v2);

//=================================================================================================================
//	��	�x�N�g���̒����Ɋւ���֐�
//=================================================================================================================
/// <summary>
/// �m����
/// </summary>
/// <param name="vec3"></param>
/// <returns></returns>
float Length(const Vec3f& vec3);

/// <summary>
/// ���K��
/// </summary>
/// <param name="vec3"></param>
/// <returns></returns>
Vec3f Normalize(const Vec3f& vec3);
