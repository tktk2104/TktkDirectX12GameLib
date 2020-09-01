#ifndef MATRIX_4_H_
#define MATRIX_4_H_

#include <ostream>

namespace tktkMath
{
	struct Vector3;
	struct Quaternion;

	struct Matrix4
	{
	public:

		// コンストラクタ
		constexpr Matrix4() = default;
		constexpr Matrix4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44)
		{
			m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
			m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
			m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
			m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
		}

	public:

		// 移動行列を生成
		static Matrix4 createTranslation(const Vector3& translation);
		// クオータニオンから回転行列を生成
		static Matrix4 createFromQuaternion(const Quaternion& rotate);
		// x軸の回転行列を生成
		static Matrix4 createRotationX(float degree);
		// y軸の回転行列を生成
		static Matrix4 createRotationY(float degree);
		// z軸の回転行列を生成
		static Matrix4 createRotationZ(float degree);
		// ヨー、ピッチ、ロールで回転行列を生成（引数は度数法）
		static Matrix4 createFromYawPitchRoll(float yaw, float pitch, float roll);
		// 任意の軸の回転行列を生成
		static Matrix4 createFromAxisAngle(const Vector3& axis, float degree);
		// スケール行列を生成
		static Matrix4 createScale(const Vector3& scale);
		// 移動、回転、スケールの値から行列を生成
		static Matrix4 createTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale);
		// 逆行列を計算
		static Matrix4 calculateInvert(const Matrix4& matrix);
		// 制限付きだが、逆行列を高速で計算（回転と平行移動のみ）
		static Matrix4 calculateInvertFast(const Matrix4& matrix);
		// 転置行列を計算
		static Matrix4 calculateTranspose(const Matrix4& matrix);
		// 2つの行列の対応する値の間を線形補間します
		static Matrix4 lerp(const Matrix4& value1, const Matrix4& value2, float amount);
		// 回転行列を正規化します。
		static Matrix4 normalizeRotationMatrix(const Matrix4& matrix);
		// スクリーン座標系に変換する行列を生成
		static Matrix4 createScreen(float x, float y, float width, float height);
		// 左手座標系のビュー行列を生成（DirectX等）
		static Matrix4 createLookAtLH(const Vector3& position, const Vector3& target, const Vector3& up);
		// 右手座標系のビュー行列を生成（OpenGL等）
		static Matrix4 createLookAtRH(const Vector3& position, const Vector3& target, const Vector3& up);
		// 左手座標系の平行投影行列を生成（DirectX等）
		static Matrix4 createOrthographicLH(float width, float height, float zn, float zf);
		// 左手座標系のパースペクティブ射影行列を生成（DirectX等）
		static Matrix4 createPerspectiveFieldOfViewLH(float fov, float aspect, float zn, float zf);
		// 右手座標系のパースペクティブ射影行列を生成（OpenGL等）
		static Matrix4 createPerspectiveFieldOfViewRH(float fov, float aspect, float zn, float zf);

	public:

		// 移動の値を再設定
		void setTranslation(const Vector3& translation);
		// 移動、回転、スケールの値を再設定
		void setTRS(const Vector3& translation, const Quaternion& rotate, const Vector3& scale);
		// 座標を計算
		Vector3 calculateTranslation() const;
		// 回転を計算
		Quaternion calculateRotation() const;
		// スケール値を計算
		Vector3 calculateScale() const;
		// 左手座標系の前方ベクトルを計算（DirectX等）
		Vector3 calculateForwardLH() const;
		// 右手座標系の前方ベクトルを計算（OpenGL等）
		Vector3 calculateForwardRH() const;
		// 上方ベクトルを計算
		Vector3 calculateUp() const;
		// 右ベクトルを計算
		Vector3 calculateRight() const;
		// 逆行列を計算
		Matrix4 calculateInvert() const;
		// 転置行列を計算
		Matrix4 calculateTranspose() const;
		// 座標変換（通常）
		Vector3 multiplyPoint(const Vector3& point);
		// 座標変換（高速）
		Vector3 multiplyPointFast(const Vector3& point);
		// ベクトル変換（平行移動無し）
		Vector3 multiplyVector(const Vector3& vector);
		// フォーマットされた文字列に変換
		std::string toString() const;

	public:

		// 各要素
		float m[4][4]{
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 0.0f }
		};
	};

	// Matrix4構造体の定数達
	struct Matrix4_v
	{
		static constexpr Matrix4 zero {
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f
		};

		static constexpr Matrix4 identity {
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	};

	// 定数達（非推奨：「Matrix4_v::」を使ってください）
	constexpr Matrix4 mat4Zero		{ 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
	constexpr Matrix4 mat4Identity	{ 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

	// 演算子オーバーロード達
	Matrix4			operator - (const Matrix4& v);
	Matrix4&		operator += (Matrix4& m1, const Matrix4& m2);
	Matrix4&		operator -= (Matrix4& m1, const Matrix4& m2);
	Matrix4&		operator *= (Matrix4& m1, const Matrix4& m2);
	Matrix4&		operator *= (Matrix4& m, float s);
	Matrix4&		operator /= (Matrix4& m, float s);
	Matrix4			operator * (Matrix4 m1, const Matrix4& m2);
	Matrix4			operator * (Matrix4 m, float s);
	Matrix4			operator * (Matrix4 s, float m);
	Vector3			operator * (const Vector3& v, const Matrix4& m);
	Matrix4			operator + (Matrix4 m1, const Matrix4& m2);
	Matrix4			operator - (Matrix4 m1, const Matrix4& m2);
	Matrix4			operator * (Matrix4 m, float s);
	Matrix4			operator * (float s, Matrix4 m);
	Matrix4			operator / (Matrix4 m, float s);
	std::ostream&	operator<<(std::ostream& os, const Matrix4& matrix);
}
#endif // !MATRIX_4_H_