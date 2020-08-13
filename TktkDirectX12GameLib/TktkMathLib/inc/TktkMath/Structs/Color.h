#ifndef COLOR_H_
#define COLOR_H_

#include <ostream>
#include <string>

namespace tktkMath
{
	struct Color
	{
	public:

		// コンストラクタ
		constexpr Color() = default;
		constexpr Color(float rgb, float a)					: r(rgb), g(rgb), b(rgb), a(a) {}
		constexpr Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		// 2つのカラー間の線形補間を行います
		static Color lerp(const Color& value1, const Color& value2, float amount);
		//	値を指定された範囲内に制限します
		static Color clamp(const Color& value1, const Color& min = Color(0.0f, 0.0f, 0.0f, 0.0f), const Color& max = Color(1.0f, 1.0f, 1.0f, 1.0f));
		// 一致する各成分ペアの最も低い値を含むカラーを返します
		static Color calculateMin(const Color& value1, const Color& value2);
		// 一致する各成分ペアの最も高い値を含むカラーを返します
		static Color calculateMax(const Color& value1, const Color& value2);

	public:

		// フォーマットされた文字列に変換
		std::string toString() const;

	public:

		// 各要素
		float r{ 0.0f };
		float g{ 0.0f };
		float b{ 0.0f };
		float a{ 1.0f };
	};

	// Color構造体の定数達
	struct Color_v
	{
		static constexpr Color black	{ 0.0f, 1.0f };
		static constexpr Color white	{ 1.0f, 1.0f };
		static constexpr Color red		{ 1.0f, 0.0f, 0.0f, 1.0f };
		static constexpr Color green	{ 0.0f, 1.0f, 0.0f, 1.0f };
		static constexpr Color blue		{ 0.0f, 0.0f, 1.0f, 1.0f };
	};

	// 定数達（非推奨：「Color_v::」を使ってください）
	constexpr Color colorBlack	{ 0.0f, 1.0f };
	constexpr Color colorWhite	{ 1.0f, 1.0f };
	constexpr Color colorRed	{ 1.0f, 0.0f, 0.0f, 1.0f };
	constexpr Color colorGreen	{ 0.0f, 1.0f, 0.0f, 1.0f };
	constexpr Color colorBlue	{ 0.0f, 0.0f, 1.0f, 1.0f };

	// 演算子オーバーロード達
	Color&			operator += (Color& c1, const Color& c2);
	Color&			operator -= (Color& c1, const Color& c2);
	Color&			operator *= (Color& c1, const Color& c2);
	Color&			operator *= (Color& c, float s);
	Color&			operator /= (Color& c, float s);
	Color			operator +  (Color c1, const Color& c2);
	Color			operator -  (Color c1, const Color& c2);
	Color			operator *  (Color c1, const Color& c2);
	Color			operator *  (Color c, float s);
	Color			operator *  (float s, Color c);
	Color			operator /  (Color c, float s);
	std::ostream&	operator << (std::ostream& os, const Color& color);
}
#endif