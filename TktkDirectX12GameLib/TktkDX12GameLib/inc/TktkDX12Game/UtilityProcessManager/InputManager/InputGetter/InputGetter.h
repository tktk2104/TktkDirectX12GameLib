#ifndef INPUT_GETTER_H_
#define INPUT_GETTER_H_

/* std::unique_ptr */
#include <memory>

/* HINSTANCE, HWND */
#include <Windows.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "MouseInputGetter/MouseBtnType.h"
#include "DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"

namespace tktk
{
	class MouseInputGetter;
	class DirectInputWrapper;

	// ���͎�t�N���X
	class InputGetter
	{
	public:

		InputGetter(HINSTANCE hInstance, HWND handle, float padStickPlayWidth);
		~InputGetter();

	public:

		void update();

	public: /* �}�E�X�֘A�̏��� */

		// �w��̃{�^����������Ă��邩
		bool isPush(MouseBtnType btnType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(MouseBtnType btnType) const;

		// �}�E�X�J�[�\���̍��W���擾����
		tktkMath::Vector2 mousePos(HWND hWnd) const;

	public: /* �L�[�{�[�h�֘A�̏��� */

		// �w��̃L�[��������Ă��邩�𔻒�
		bool isPush(KeybordKeyType keyType) const;

		// �w��̃L�[��������n�߂����𔻒�
		bool isTrigger(KeybordKeyType keyType) const;

	public: /* �Q�[���p�b�h�֘A�̏��� */

		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getLstick() const;

		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getRstick() const;

		// �w��̃{�^����������Ă��邩�𔻒�
		bool isPush(GamePadBtnType btnType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(GamePadBtnType btnType) const;

	private:

		std::unique_ptr<MouseInputGetter>				m_mouse;
		std::unique_ptr<DirectInputWrapper> m_directInputWrapper;
	};
}
#endif // !INPUT_GETTER_H_