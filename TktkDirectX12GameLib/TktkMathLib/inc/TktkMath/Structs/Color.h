#ifndef COLOR_H_
#define COLOR_H_

#include <ostream>
#include <string>

namespace tktkMath
{
	struct Color
	{
	public:

		// �R���X�g���N�^
		constexpr Color() = default;
		constexpr Color(float rgb, float a)					: r(rgb), g(rgb), b(rgb), a(a) {}
		constexpr Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

		// 2�̃J���[�Ԃ̐��`��Ԃ��s���܂�
		static Color lerp(const Color& value1, const Color& value2, float amount);
		//	�l���w�肳�ꂽ�͈͓��ɐ������܂�
		static Color clamp(const Color& value1, const Color& min = Color(0.0f, 0.0f, 0.0f, 0.0f), const Color& max = Color(1.0f, 1.0f, 1.0f, 1.0f));
		// ��v����e�����y�A�̍ł��Ⴂ�l���܂ރJ���[��Ԃ��܂�
		static Color calculateMin(const Color& value1, const Color& value2);
		// ��v����e�����y�A�̍ł������l���܂ރJ���[��Ԃ��܂�
		static Color calculateMax(const Color& value1, const Color& value2);

	public:

		// �t�H�[�}�b�g���ꂽ������ɕϊ�
		std::string toString() const;

	public:

		// �e�v�f
		float r{ 0.0f };
		float g{ 0.0f };
		float b{ 0.0f };
		float a{ 1.0f };
	};

	// Color�\���̂̒萔�B
	struct Color_v
	{
		static constexpr Color black	{ 0.0f, 1.0f };
		static constexpr Color white	{ 1.0f, 1.0f };
		static constexpr Color red		{ 1.0f, 0.0f, 0.0f, 1.0f };
		static constexpr Color green	{ 0.0f, 1.0f, 0.0f, 1.0f };
		static constexpr Color blue		{ 0.0f, 0.0f, 1.0f, 1.0f };
	};

	// ���Z�q�I�[�o�[���[�h�B
	Color&			operator += (Color& c1, const Color& c2);
	Color&			operator -= (Color& c1, const Color& c2);
	Color&			operator *= (Color& c1, const Color& c2);
	template <class T>
	Color&			operator *= (Color& c, T s) { c.r *= s; c.g *= s; c.b *= s; c.a *= s; return c; };
	template <class T>
	Color&			operator /= (Color& c, T s) { c.r /= s; c.g /= s; c.b /= s; c.a /= s; return c; };
	Color			operator +  (Color c1, const Color& c2);
	Color			operator -  (Color c1, const Color& c2);
	Color			operator *  (Color c1, const Color& c2);
	template <class T>
	Color			operator *  (Color c, T s) { return c *= s; };
	template <class T>
	Color			operator *  (T s, Color c) { return c *= s; };
	template <class T>
	Color			operator /  (Color c, T s) { return c /= s; };
	std::ostream&	operator << (std::ostream& os, const Color& color);
}
#endif