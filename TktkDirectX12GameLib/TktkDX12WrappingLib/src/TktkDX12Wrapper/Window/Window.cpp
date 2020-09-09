#include "TktkDX12Wrapper/Window/Window.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

namespace tktk
{
	Window::Window(const WindowInitParam& initParam)
		: m_windowSize(initParam.windowSize)
	{
#ifdef _M_AMD64 /* x64ビルドなら */

		// ワイド文字列に変換
		std::wstring wstrWindowName(initParam.windowName.begin(), initParam.windowName.end());

		// ウィンドウクラスを生成
		WNDCLASS wc{};
		wc.lpfnWndProc = WndProc;
		wc.hInstance = initParam.hInstance;
		wc.lpszClassName = wstrWindowName.c_str();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&wc);

		// ウィンドウサイズを計算
		RECT rect{ 0, 0, static_cast<int>(initParam.windowSize.x), static_cast<int>(initParam.windowSize.y) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ウィンドウを生成
		m_hwnd = CreateWindow(
			wstrWindowName.c_str(),
			wstrWindowName.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			initParam.hInstance,
			NULL
		);
#else
		// ウィンドウクラスを生成
		WNDCLASS wc{};
		wc.lpfnWndProc = WndProc;
		wc.hInstance = initParam.hInstance;
		wc.lpszClassName = initParam.windowName.c_str();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&wc);

		// ウィンドウサイズを計算
		RECT rect{ 0, 0, static_cast<int>(initParam.windowSize.x), static_cast<int>(initParam.windowSize.y) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		// ウィンドウを生成
		m_hwnd = CreateWindow(
			initParam.windowName.c_str(),
			initParam.windowName.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			rect.right - rect.left,
			rect.bottom - rect.top,
			NULL,
			NULL,
			initParam.hInstance,
			NULL
		);
#endif // _M_AMD64

		if (m_hwnd == NULL)
		{
			throw std::runtime_error("CreateWindow error");
		}

		// ウィンドウを開く
		ShowWindow(m_hwnd, initParam.nCmdShow);

		// 初回更新
		UpdateWindow(m_hwnd);
	}

	HWND Window::getHWND() const
	{
		return m_hwnd;
	}

	const tktkMath::Vector2& Window::getWindowSize() const
	{
		return m_windowSize;
	}
}