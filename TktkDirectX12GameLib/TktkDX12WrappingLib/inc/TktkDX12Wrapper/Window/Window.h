#ifndef WINDOW_H_
#define WINDOW_H_

#include <TktkMath/Structs/Vector2.h>
#include "../Includer/WindowsHeaderIncluder.h"
#include "WindowInitParam.h"

namespace tktk
{
	// ゲームのウィンドウを管理するクラス
	class Window
	{
	public:

		explicit Window(const WindowInitParam& initParam);
		~Window() = default;

		// コピー禁止
		Window(const Window& other) = delete;
		Window& operator = (const Window& other) = delete;

	public:

		// ウィンドウハンドルを取得する
		HWND getHWND() const;

		// ウィンドウサイズを取得する
		const tktkMath::Vector2& getWindowSize() const;

	private:

		// ウィンドウハンドル
		HWND m_hwnd{ nullptr };

		// ウィンドウサイズ
		tktkMath::Vector2 m_windowSize{ };
	};
}
#endif // !WINDOW_H_