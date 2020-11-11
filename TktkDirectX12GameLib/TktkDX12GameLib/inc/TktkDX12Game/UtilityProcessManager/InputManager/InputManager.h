#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

/* std::unique_ptr */
#include <memory>

/* HINSTANCE, HWND */
#include <Windows.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "InputGetter/MouseInputGetter/MouseBtnType.h"
#include "InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"
#include "CommandTypeManager/CommandIdCarrier.h"
#include "CommandTypeManager/DirectionCommandId.h"

namespace tktk
{
	class InputGetter;
	class CommandTypeManager;

	// ���͊Ǘ��N���X
	class InputManager
	{
	public:

		explicit InputManager(HINSTANCE hInstance, HWND handle, float padStickPlayWidth);
		~InputManager();

	public:

		void update();

	public: /* �R�}���hID���g�p�������� */

		// ID�ɑΉ��������͂�������Ă��邩�𔻒�
		bool isPush(CommandIdCarrier commandId) const;

		// ID�ɑΉ��������͂�������n�߂����𔻒�
		bool isTrigger(CommandIdCarrier commandId) const;

		// �ړ��������擾
		const tktkMath::Vector2& moveVec()const;

		// ���_�ړ��������擾
		const tktkMath::Vector2& lookVec()const;

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

	public:

		// �e����͂Ɠ��̓R�}���hID�����т���
		void addCommand(CommandIdCarrier commandId, MouseBtnType btnType);
		void addCommand(CommandIdCarrier commandId, KeybordKeyType keyType);
		void addCommand(CommandIdCarrier commandId, GamePadBtnType btnType);

		// �e����͂ƈړ����̓R�}���hID�����т���
		void addDirectionCommand(DirectionCommandId directionCommandId, MouseBtnType btnType);
		void addDirectionCommand(DirectionCommandId directionCommandId, KeybordKeyType keyType);
		void addDirectionCommand(DirectionCommandId directionCommandId, GamePadBtnType btnType);

	private:

		// ���݂̈ړ�����
		tktkMath::Vector2 m_curMoveVec{};

		// ���݂̎��_�ړ�����
		tktkMath::Vector2 m_curLookVec{};

		std::unique_ptr<InputGetter>		m_inputGetter;
		std::unique_ptr<CommandTypeManager> m_commandTypeManager;
	};
}
#endif // !INPUT_MANAGER_H_