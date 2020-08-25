#ifndef SYSTEM_VIEWPORT_TYPE_H_
#define SYSTEM_VIEWPORT_TYPE_H_

namespace tktk
{
	// システムで使用しているビューポートの数
	constexpr unsigned int SystemViewportNum = 1U;

	// システムで使用しているビューポートの種類
	enum class SystemViewportType
	{
		Basic = 0U
	};
}
#endif // !SYSTEM_VIEWPORT_TYPE_H_