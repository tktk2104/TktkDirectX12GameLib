#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <unordered_map>
#include <TktkMath/Structs/Vector2.h>
#include "../DirectInputWrapper/Keyboard/Keyboard.h"
#include "../DirectInputWrapper/GamePad/GamePad.h"
#include "../Mouse/Mouse.h"
#include "DirectionCommandType.h"

namespace tktk
{
	class InputManager
	{
	public:

		explicit InputManager(float padStickPlayWidth);

	public:

		void update();

	public:

		// ID�ɑΉ��������͂�������Ă��邩�𔻒�
		bool isPush(int commandId) const;

		// ID�ɑΉ��������͂�������n�߂����𔻒�
		bool isTrigger(int commandId) const;

		// �ړ��������擾
		const tktkMath::Vector2& moveVec()const;

		// ���_�ړ��������擾
		const tktkMath::Vector2& lookVec()const;

	public:

		// �e����͂�ID�����т���
		void addCommand(int commandId, KeybordKeyType keyType);
		void addCommand(int commandId, GamePadBtnType btnType);
		void addCommand(int commandId, MouseButtonType btnType);

		// �e����͂ƈړ��R�}���h�����т���
		void addDirectionCommand(DirectionCommandType directionCommand, KeybordKeyType keyType);
		void addDirectionCommand(DirectionCommandType directionCommand, GamePadBtnType btnType);
		void addDirectionCommand(DirectionCommandType directionCommand, MouseButtonType btnType);

	private:

		// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̌X���̗V��
		float m_padStickPlayWidth{};

		// ���݂̈ړ�����
		tktkMath::Vector2 m_curMoveVec{};

		// ���݂̎��_�ړ�����
		tktkMath::Vector2 m_curLookVec{};

		// ���ꂼ��̓��͂̎�ނƈړ��R�}���h�̑Ή��\
		std::unordered_multimap<DirectionCommandType, KeybordKeyType>	m_keyDirectionCommandMap;
		std::unordered_multimap<DirectionCommandType, GamePadBtnType>	m_padDirectionCommandMap;
		std::unordered_multimap<DirectionCommandType, MouseButtonType>	m_mouseDirectionCommandeMap;

		// ���ꂼ��̓��͂̎�ނ�ID�̑Ή��\
		std::unordered_multimap<int, KeybordKeyType>		m_keyCommandMap;
		std::unordered_multimap<int, GamePadBtnType>		m_padCommandMap;
		std::unordered_multimap<int, MouseButtonType>	m_mouseCommandMap;
	};
}
#endif // !INPUT_MANAGER_H_