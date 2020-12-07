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

	// �Q�[���̃E�B���h�E���Ǘ�����N���X
	class Window
	{
	public:

		explicit Window(const WindowInitParam& initParam);
		~Window();

		// �R�s�[�֎~
		Window(const Window& other) = delete;
		Window& operator = (const Window& other) = delete;

	public:

		// �E�B���h�E�n���h�����擾����
		HWND getHWND() const;

		// �Q�[���`��G���A�T�C�Y���擾����
		const tktkMath::Vector2& getDrawGameAreaSize() const;

		// �X�N���[���T�C�Y���擾����
		const tktkMath::Vector2& getScreenSize() const;

	private:

		// �E�B���h�E�n���h��
		HWND m_hwnd{ nullptr };

		// �Q�[���`��G���A�T�C�Y
		tktkMath::Vector2 m_drawGameAreaSize;

		// �X�N���[���T�C�Y
		tktkMath::Vector2 m_screenSize;
	};
}
#endif // !WINDOW_H_