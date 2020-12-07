#include "TktkDX12Game/GraphicManager/Window/Window.h"

#include "TktkDX12Game/GraphicManager/Window/WindowInitParam.h"

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
{//WS_THICKFRAME
	Window::Window(const WindowInitParam& initParam)
		: m_drawGameAreaSize(initParam.windowSize)
	{
		if (initParam.fullScreen)
		{
			m_screenSize = { 
				static_cast<float>(GetSystemMetrics(SM_CXSCREEN)),
				static_cast<float>(GetSystemMetrics(SM_CYSCREEN))
			};
		}
		else
		{
			m_screenSize = m_drawGameAreaSize;
		}


#ifdef _M_AMD64 /* x64�r���h�Ȃ� */

		// ���C�h������ɕϊ�
		std::wstring wstrWindowName(initParam.windowName.begin(), initParam.windowName.end());

		// �E�B���h�E�N���X�𐶐�
		WNDCLASS wc{};
		wc.lpfnWndProc = WndProc;
		wc.hInstance = initParam.hInstance;
		wc.lpszClassName = wstrWindowName.c_str();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&wc);

		// �E�B���h�E�T�C�Y���v�Z
		RECT rect{ 0, 0, static_cast<int>(m_screenSize.x), static_cast<int>(m_screenSize.y) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		auto baseDwStyle = (initParam.fullScreen) ? WS_POPUP : WS_OVERLAPPEDWINDOW;

		// �E�B���h�E�𐶐�
		m_hwnd = CreateWindow(
			wstrWindowName.c_str(),
			wstrWindowName.c_str(),
			baseDwStyle & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
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
		// �E�B���h�E�N���X�𐶐�
		WNDCLASS wc{};
		wc.lpfnWndProc = WndProc;
		wc.hInstance = initParam.hInstance;
		wc.lpszClassName = initParam.windowName.c_str();
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		RegisterClass(&wc);

		// �E�B���h�E�T�C�Y���v�Z
		RECT rect{ 0, 0, static_cast<int>(m_screenSize.x), static_cast<int>(m_screenSize.y) };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		auto baseDwStyle = (initParam.fullScreen) ? WS_POPUP : WS_OVERLAPPEDWINDOW;

		// �E�B���h�E�𐶐�
		m_hwnd = CreateWindow(
			initParam.windowName.c_str(),
			initParam.windowName.c_str(),
			baseDwStyle & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
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

		if (m_hwnd == NULL) throw std::runtime_error("CreateWindow error");

		if (initParam.fullScreen) ShowCursor(false);

		// �E�B���h�E���J��
		ShowWindow(m_hwnd, initParam.nCmdShow);

		// ����X�V
		UpdateWindow(m_hwnd);
	}

	// �f�X�g���N�^���C�����C��������
	Window::~Window() = default;

	HWND Window::getHWND() const
	{
		return m_hwnd;
	}

	const tktkMath::Vector2& Window::getDrawGameAreaSize() const
	{
		return m_drawGameAreaSize;
	}

	const tktkMath::Vector2& Window::getScreenSize() const
	{
		return m_screenSize;
	}
}