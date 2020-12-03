#ifndef KEY_BOARD_INPUT_GETTER_H_
#define KEY_BOARD_INPUT_GETTER_H_

/* std::vector */
#include <vector>

/* directInput */
#define DIRECTINPUT_VERSION     0x0800
#include <dinput.h>
#undef min
#undef max

/* funcUseType */
#include "KeybordKeyType.h"

namespace tktk
{
	// �L�[�{�[�h�̓��͂����m����N���X
	class KeyboardInputGetter
	{
	public:

		KeyboardInputGetter(LPDIRECTINPUT8 input, HWND handle);
		~KeyboardInputGetter();

		KeyboardInputGetter(const KeyboardInputGetter& other) = delete;
		KeyboardInputGetter& operator = (const KeyboardInputGetter& other) = delete;

	public:

		void update();

	public:

		// �w��̃L�[��������Ă��邩�𔻒�
		bool isPush(KeybordKeyType keyType) const;

		// �w��̃L�[��������n�߂����𔻒�
		bool isTrigger(KeybordKeyType keyType) const;

	private:

		// �L�[���͏���ۑ�����z��̗v�f��
		static constexpr size_t			KeyDataArraySize	{ 256U };

		// �L�[���͏��̑��o�C�g��
		static constexpr unsigned int	KeyDataByteSize		{ sizeof(unsigned char) * KeyDataArraySize };

	private:

		// �C���v�b�g�f�o�C�X
		LPDIRECTINPUTDEVICE8		m_inputDevice	{ nullptr };

		// ���݂̃L�[���͏��
		std::vector<unsigned char>	m_curKeys		{};

		// �O�t���[���̃L�[���͏��
		std::vector<unsigned char>	m_preKeys		{};
	};
}
#endif // !KEY_BOARD_INPUT_GETTER_H_