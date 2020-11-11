#ifndef GAME_PAD_INPUT_GETTER_H_
#define GAME_PAD_INPUT_GETTER_H_

/* std::unique_ptr */
#include <memory>

/* directInput */
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "GamePadBtnType.h"

namespace tktk
{
	// �Q�[���p�b�h���͌��m�N���X
	class GamePadInputGetter
	{
	public:

		GamePadInputGetter(LPDIRECTINPUT8 input, HWND handle, float padStickPlayWidth);
		~GamePadInputGetter();

	public:

		void update();

	public:

		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getLstick() const;

		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		tktkMath::Vector2 getRstick() const;

		// �w��̃{�^����������Ă��邩�𔻒�
		bool isPush(GamePadBtnType btnType) const;

		// �w��̃{�^����������n�߂����𔻒�
		bool isTrigger(GamePadBtnType btnType) const;

	private:

		// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̌X���̗V��
		float							m_padStickPlayWidth;

		// �C���v�b�g�f�o�C�X
		LPDIRECTINPUTDEVICE8			m_inputDevice{ nullptr };

		// �Q�[���p�b�h�����������H
		bool							m_findGamePad{ false };

		// ���݂̃p�b�h���͏��
		std::unique_ptr<DIJOYSTATE2>	m_curPadState;

		// �O�t���[���̃p�b�h���͏��
		std::unique_ptr<DIJOYSTATE2>	m_prePadState;
	};
}
#endif // !GAME_PAD_INPUT_GETTER_H_