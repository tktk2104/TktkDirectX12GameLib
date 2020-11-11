#ifndef MOUSE_INPUT_GETTER_H_
#define MOUSE_INPUT_GETTER_H_

/* std::unordered_map */
#include <unordered_map>

/* HWND */
#include <windows.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "MouseBtnType.h"

namespace tktk
{
	// �}�E�X���͎擾�N���X
	class MouseInputGetter
	{
	public:

		MouseInputGetter();
		~MouseInputGetter();

		MouseInputGetter(const MouseInputGetter& other) = delete;
		MouseInputGetter& operator = (const MouseInputGetter& other) = delete;

	public:

		void update();

	public:

		// �w��̃{�^����������Ă��邩
		bool isPush(MouseBtnType btnType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(MouseBtnType btnType) const;

		// �}�E�X�J�[�\���̍��W���擾����
		tktkMath::Vector2 mousePos(HWND hWnd) const;

	private:

		std::unordered_map<MouseBtnType, bool> m_curMouseBtnState;
		std::unordered_map<MouseBtnType, bool> m_preMouseBtnState;
	};
}
#endif // !MOUSE_INPUT_GETTER_H_
