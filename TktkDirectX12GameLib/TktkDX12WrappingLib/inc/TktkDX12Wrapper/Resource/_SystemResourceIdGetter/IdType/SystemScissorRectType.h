#ifndef SYSTEM_SCISSOR_RECT_TYPE_H_
#define SYSTEM_SCISSOR_RECT_TYPE_H_

namespace tktk
{
	// システムで使用しているシザー矩形の数
	constexpr unsigned int SystemScissorRectNum = 1U;

	// システムで使用しているシザー矩形の種類
	enum class SystemScissorRectType
	{
		Basic = 0U
	};
}
#endif // !SYSTEM_SCISSOR_RECT_TYPE_H_