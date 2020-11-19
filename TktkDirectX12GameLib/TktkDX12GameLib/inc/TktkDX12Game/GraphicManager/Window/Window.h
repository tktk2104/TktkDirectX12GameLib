#ifndef WINDOW_H_
#define WINDOW_H_

/* HWND */
#include <Windows.h>
#undef min
#undef max

/* class member */
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	/* funcUseType */
	struct WindowInitParam;

	// ゲームのウィンドウを管理するクラス
	class Window
	{
	public:

		explicit Window(const WindowInitParam& initParam);
		~Window();

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