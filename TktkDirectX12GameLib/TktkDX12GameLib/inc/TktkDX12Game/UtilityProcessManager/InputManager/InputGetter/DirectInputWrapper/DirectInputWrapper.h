#ifndef DIRECT_INPUT_WRAPPER_H_
#define DIRECT_INPUT_WRAPPER_H_

/* std::unique_ptr */
#include <memory>

/* directInput */
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "KeyboardInputGetter/KeybordKeyType.h"
#include "GamePadInputGetter/GamePadBtnType.h"

namespace tktk
{
	// �O���錾�B
	class KeyboardInputGetter;
	class GamePadInputGetter;

	// �_�C���N�g�C���v�b�g�ł̓��͔��菈��
	class DirectInputWrapper
	{
	public:

		DirectInputWrapper(HINSTANCE hInstance, HWND handle, float padStickPlayWidth);
		~DirectInputWrapper();

	public:

		void update();

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

		// �C���v�b�g
		LPDIRECTINPUT8							m_input		{ nullptr };

		// �L�[�{�[�h
		std::unique_ptr<KeyboardInputGetter>	m_keyboard	{ nullptr };

		// �Q�[���p�b�h
		std::unique_ptr<GamePadInputGetter>		m_gamePad	{ nullptr };
	};
}
#endif // !DIRECT_INPUT_WRAPPER_H_