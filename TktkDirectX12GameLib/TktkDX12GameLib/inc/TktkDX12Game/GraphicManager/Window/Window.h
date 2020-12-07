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

		// ゲーム描画エリアサイズを取得する
		const tktkMath::Vector2& getDrawGameAreaSize() const;

		// スクリーンサイズを取得する
		const tktkMath::Vector2& getScreenSize() const;

	private:

		// ウィンドウハンドル
		HWND m_hwnd{ nullptr };

		// ゲーム描画エリアサイズ
		tktkMath::Vector2 m_drawGameAreaSize;

		// スクリーンサイズ
		tktkMath::Vector2 m_screenSize;
	};
}
#endif // !WINDOW_H_