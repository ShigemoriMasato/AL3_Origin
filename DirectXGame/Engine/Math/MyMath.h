#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <cmath>
#include "../Data/Vector.h"
#include "../Data/Matrix.h"
#include "../Data/Transform.h"

Vector2 operator+(const Vector2& a, const Vector2& b);
Vector2 operator-(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const Vector2& b);
Vector2 operator*(const Vector2& a, float b);
Vector2 operator*(float a, const Vector2& b);
Vector2 operator/(const Vector2& a, const Vector2& b);
Vector2 operator/(const Vector2& a, float b);
Vector2 operator+=(Vector2& a, const Vector2& b);
Vector2 operator-=(Vector2& a, const Vector2& b);
Vector2 operator*=(Vector2& a, const Vector2& b);
Vector2 operator*=(Vector2& a, float b);
Vector2 operator/=(Vector2& a, const Vector2& b);
Vector2 operator/=(Vector2& a, float b);
bool operator==(const Vector2& a, const Vector2& b);
bool operator!=(const Vector2& a, const Vector2& b);

Vector3 operator+(const Vector3& a, const Vector3& b);
Vector3 operator-(const Vector3& a, const Vector3& b);
Vector3 operator*(const Vector3& a, const Vector3& b);
Vector3 operator*(const Vector3& a, float b);
Vector3 operator*(float a, const Vector3& b);
Vector3 operator/(const Vector3& a, const Vector3& b);
Vector3 operator/(const Vector3& a, float b);
Vector3 operator+=(Vector3& a, const Vector3& b);
Vector3 operator-=(Vector3& a, const Vector3& b);
Vector3 operator*=(Vector3& a, const Vector3& b);
Vector3 operator*=(Vector3& a, float b);
Vector3 operator/=(Vector3& a, const Vector3& b);
Vector3 operator/=(Vector3& a, float b);
bool operator==(const Vector3& a, const Vector3& b);
bool operator!=(const Vector3& a, const Vector3& b);

Vector4 operator+(const Vector4& a, const Vector4& b);
Vector4 operator-(const Vector4& a, const Vector4& b);
Vector4 operator*(const Vector4& a, const Vector4& b);
Vector4 operator*(const Vector4& a, float b);
Vector4 operator*(float a, const Vector4& b);
Vector4 operator/(const Vector4& a, const Vector4& b);
Vector4 operator/(const Vector4& a, float b);
Vector4 operator+=(Vector4& a, const Vector4& b);
Vector4 operator-=(Vector4& a, const Vector4& b);
Vector4 operator*=(Vector4& a, const Vector4& b);
Vector4 operator*=(Vector4& a, float b);
Vector4 operator/=(Vector4& a, const Vector4& b);
Vector4 operator/=(Vector4& a, float b);
bool operator==(const Vector4& a, const Vector4& b);
bool operator!=(const Vector4& a, const Vector4& b);

Matrix3x3 operator+(const Matrix3x3& a, const Matrix3x3& b);
Matrix3x3 operator-(const Matrix3x3& a, const Matrix3x3& b);
Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b);
Vector2 operator*(const Matrix3x3& a, const Vector2& b);
Vector2 operator*(const Vector2& a, const Matrix3x3& b);
Matrix3x3 operator/(const Matrix3x3& a, const Matrix3x3& b);
Matrix3x3 operator+=(Matrix3x3& a, const Matrix3x3& b);
Matrix3x3 operator-=(Matrix3x3& a, const Matrix3x3& b);
Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b);
bool operator==(const Matrix3x3& a, const Matrix3x3& b);
bool operator!=(const Matrix3x3& a, const Matrix3x3& b);

Matrix4x4 operator+(const Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator-(const Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
Vector3 operator*(const Matrix4x4& a, const Vector3& b);
Vector3 operator*(const Vector3& a, const Matrix4x4& b);
Matrix4x4 operator/(const Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator+=(Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator-=(Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b);
Matrix4x4 operator/=(Matrix4x4& a, const Matrix4x4& b);
bool operator==(const Matrix4x4& a, const Matrix4x4& b);
bool operator!=(const Matrix4x4& a, const Matrix4x4& b);

namespace Matrix {

	Matrix4x4 Inverse(const Matrix4x4& m);
	Matrix3x3 Inverse(const Matrix3x3& m);

	Matrix4x4 MakeTranslationMatrix(const Vector3& pos);
	Matrix4x4 MakeRotationMatrix(Vector3 angle);
	Matrix4x4 MakeScaleMatrix(const Vector3& scale);
	Matrix4x4 MakeAffineMatrix(const Vector3& pos, const Vector3& angle, const Vector3& scale);
	Matrix4x4 MakeAffineMatrix(Transform transform);

	Matrix3x3 MakeTranslationMatrix(const Vector2& pos);
	Matrix3x3 MakeRotationMatrix(float angle);
	Matrix3x3 MakeScaleMatrix(const Vector2& scale);
	Matrix3x3 MakeAffineMatrix(const Vector2& pos, float angle, const Vector2& scale);

	Matrix3x3 MakeIdentity3x3();
	Matrix4x4 MakeIdentity4x4();
}

namespace MyMath {
	float lerp(float a, float b, float t);

	/// <summary>
	/// RGBAを線形補完
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	uint32_t lerp(uint32_t a, uint32_t b, float t);

	float EaseIn(float a, float b, float t);
	Vector3 EaseIn(Vector3 a, Vector3 b, float t);

	float EaseOut(float a, float b, float t);
	Vector3 EaseOut(Vector3 a, Vector3 b, float t);



	Vector3 ConvertVector(const Vector4& v);

	float cot(float radian);

	Vector3 Normalize(Vector3 vec);
}

namespace Collision {
	bool AABBtoAABB(AABB a, AABB b);
}
