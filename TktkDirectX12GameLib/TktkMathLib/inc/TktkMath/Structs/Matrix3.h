#ifndef MATRIX3_H_
#define MATRIX3_H_

#include <ostream>

namespace tktkMath
{
	struct Vector2;

	// 3x3の行列の構造体
	struct Matrix3
	{
	public:

		// コンストラクタ
		constexpr Matrix3() = default;
		constexpr Matrix3(
			float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33)
		{
			m[0][0] = m11; m[0][1] = m12; m[0][2] = m13;
			m[1][0] = m21; m[1][1] = m22; m[1][2] = m23;
			m[2][0] = m31; m[2][1] = m32; m[2][2] = m33;
		}

	public:

		// 移動行列を生成
		static Matrix3 createTranslation(const Vector2& translation);
		// 回転行列を生成
		static Matrix3 createRotation(float degree);
		// スケール行列を生成
		static Matrix3 createScale(const Vector2& scale);
		// 移動、回転、スケールの値から行列を生成
		static Matrix3 createTRS(const Vector2& translation, float rotate, const Vector2& scale);
		// 逆行列を生成
		static Matrix3 calculateInvert(const Matrix3& matrix);
		// 行列の行と列を入れ替えます。
		static Matrix3 calculateTranspose(const Matrix3& matrix);

	public:

		// 平行移動ベクトルを設定
		void setTranslation(const Vector2& translation);
		// 移動、回転、スケールの値を再設定
		void setTRS(const Vector2& translation, float rotate, const Vector2& scale);
		// 平行移動ベクトルを計算
		Vector2 calculateTranslation() const;
		// 回転を計算
		float calculateRotation() const;
		// スケール値を計算
		Vector2 calculateScale() const;
		// 上方ベクトルを計算
		Vector2 calculateUp() const;
		// 右ベクトルを計算
		Vector2 calculateRight() const;
		// フォーマットされた文字列に変換
		std::string toString() const;

	public:

		// 各要素
		float m[3][3]{
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f }
		};
	};

	// Matrix3構造体の定数達
	struct Matrix3_v
	{
		static constexpr Matrix3 zero {
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f
		};

		static constexpr Matrix3 identity {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
		};
	};

	// 定数達（非推奨：「Matrix3_v::」を使ってください）
	constexpr Matrix3 mat3Zero{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	constexpr Matrix3 mat3Identity{ 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// 演算子オーバーロード達
	Matrix3			operator -  (const Matrix3& m);
	Matrix3&		operator += (Matrix3& m1, const Matrix3& m2);
	Matrix3&		operator -= (Matrix3& m1, const Matrix3& m2);
	Matrix3&		operator *= (Matrix3& m1, const Matrix3& m2);
	Matrix3&		operator *= (Matrix3& m, float s);
	Matrix3&		operator /= (Matrix3& m, float s);
	Matrix3			operator +  (Matrix3 m1, const Matrix3& m2);
	Matrix3			operator -  (Matrix3 m1, const Matrix3& m2);
	Matrix3			operator *  (Matrix3 m1, const Matrix3& m2);
	Matrix3			operator *  (Matrix3 m, float s);
	Matrix3			operator *  (float s, Matrix3 m);
	Matrix3			operator /  (Matrix3 m, float s);
	Vector2			operator *	(const Vector2& v, const Matrix3& m);
	Vector2&		operator *=	(Vector2& v, const Matrix3& m);
	std::ostream&	operator << (std::ostream& os, const Matrix3& matrix);
}
#endif