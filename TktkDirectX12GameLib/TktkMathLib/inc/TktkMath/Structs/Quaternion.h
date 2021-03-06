#ifndef QUATERNION_H_
#define QUATERNION_H_

#include <ostream>
#include "TktkMath/Structs/Vector3.h"

namespace tktkMath
{
	struct Matrix4;

	// ３次元回転を表すクオータニオンの構造体
	struct Quaternion
	{
	public:

		// コンストラクタ
		constexpr Quaternion() = default;
		constexpr Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

	public:

		// インデックスで各要素にアクセスするためのオーバーロード
		float operator[](int index) const;
		float& operator[](int index);

	public:

		// オイラー角からクオータニオンを生成する
		static Quaternion createFromEulerAngle(const Vector3& euler);
		// axisの周りを degree 度だけ回転するクオータニオンを生成する
		static Quaternion createFromAxisAngle(const Vector3& axis, float degree);
		// 回転行列からクオータニオンを作成
		static Quaternion createFromRotationMatrix(const Matrix4& matrix);
		// fromからtoへの回転を求める
		static Quaternion createFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
		// 指定した方向を向いた回転を求める
		static Quaternion createLookRotation(const Vector3& view, const Vector3& up = Vector3_v::up);
		// fromからtoへの回転を求める
		static Quaternion createRotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);
		// 逆クオータニオンを計算する
		static Quaternion calculateInvert(const Quaternion& rotation);
		// ２つの回転 a と b 間の角度を計算する
		static float calculateAngle(const Quaternion& q1, const Quaternion& q2);
		// 内積を計算する
		static float calculateDot(const Quaternion& q1, const Quaternion& q2);
		// 正規化する
		static Quaternion normalize(const Quaternion& q);
		// aとbの間をtで線形補間する（tを0と1の間でクランプする）
		static Quaternion lerp(const Quaternion& value1, const Quaternion& value2, float t);
		// aとbの間をtで線形補間する
		static Quaternion lerpUnclamped(const Quaternion& value1, const Quaternion& value2, float t);
		// 球面線形補間
		static Quaternion slerp(const Quaternion& value1, const Quaternion& value2, float amount);
		// 球面線形補間
		static Quaternion slerpUnclamped(const Quaternion& value1, const Quaternion& value2, float amount);

	public:

		// クオータニオンのノルムを計算する
		float calculateLength() const;
		// オイラー角を計算する
		Vector3 calculateEulerAngle() const;
		// 各要素を再設定する
		void setValue(float x, float y, float z, float w);
		// fromからtoへの回転を自身に設定する
		void setFromToRotation(const Vector3& fromDirection, const Vector3& toDirection);
		// 指定した方向を向いた回転を自身に設定する
		void setLookRotation(const Vector3& view, const Vector3& up = Vector3_v::up);
		// ２つの回転が大体同じだったら真を返す
		bool equals(const Quaternion& other) const;
		// フォーマットされた文字列に変換
		std::string toString() const;

	public:

		float x{ 0.0f };
		float y{ 0.0f };
		float z{ 0.0f };
		float w{ 0.0f };
	};

	// Quaternion構造体の定数達
	struct Quaternion_v
	{
		static constexpr Quaternion identity { 0.0f, 0.0f, 0.0f, 1.0f };
	};

	// 演算子オーバーロード達
	Quaternion		operator -  (const Quaternion& q);
	Quaternion&		operator += (Quaternion& q1, const Quaternion& q2);
	Quaternion&		operator -= (Quaternion& q1, const Quaternion& q2);
	template <class T>
	Quaternion&		operator *= (Quaternion& q, T s)	{ q.x *= s; q.y *= s; q.z *= s; q.w *= s; return q; };
	template <class T>
	Quaternion&		operator /= (Quaternion& q, T s)	{ q.x /= s; q.y /= s; q.z /= s; q.w /= s; return q; };
	Quaternion&		operator *= (Quaternion& q1, const Quaternion& q2);
	Quaternion		operator +  (Quaternion q1, const Quaternion& q2);
	Quaternion		operator -  (Quaternion q1, const Quaternion& q2);
	Quaternion		operator *  (Quaternion q1, const Quaternion& q2);
	template <class T>
	Quaternion		operator *  (Quaternion q, T s)		{ return q *= s; };
	template <class T>
	Quaternion		operator *  (T s, Quaternion q)		{ return q *= s; };
	template <class T>
	Quaternion		operator /  (Quaternion q, T s)		{ return q /= s; };
	Vector3			operator *  (const Vector3& point, const Quaternion& rotation);
	std::ostream&	operator << (std::ostream& os, const Quaternion& quaternion);
}
#endif // !QUATERNION_H_