#ifndef TKTK_DX12_GAME_H_
#define TKTK_DX12_GAME_H_

#include <forward_list>
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "EventMessage/MessageTypeCarrier.h"
#include "EventMessage/MessageAttachment.h"
#include "GameObject/GameObjectPtr.h"
#include "GameObject/GameObjectTagCarrier.h"
#include "DXGameResource/_HandleGetter/ResourceIdCarrier.h"
#include "Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "_MainManager/DX12GameManagerFuncArgsIncluder.h"

namespace tktk
{
	// �Q�[���̊e�폈�����Ă�
	// ���ׂ����������Ăт����ꍇ�́uDX12GameManager�v���g���Ă�������
	class DX12Game
	{
	//************************************************************
	/* �E�B���h�E�̏��� */
	public:

		// �E�B���h�E�T�C�Y���擾����
		static const tktkMath::Vector2& getWindowSize();

	//************************************************************
	/* �V�[���̏��� */
	public:

		// �V�[����L���ɂ���
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		static void enableScene(ResourceIdCarrier id);

		// �V�[���𖳌��ɂ���
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		static void disableScene(ResourceIdCarrier id);

	//************************************************************
	/* �Q�[���I�u�W�F�N�g�̏��� */
	public:

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		static void sendMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment = {});

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		static GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// ���Y���I�u�W�F�N�g�����������ꍇ�A���GameObjectPtr���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		static GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag);

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag);

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�č폜����
		static void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	//************************************************************
	/* ���͊֌W�̏��� */
	public:

		// ����̓��͂�������Ă��邩���n�߂�
		// �u�Ή�������́FMouseButtonType, KeybordKeyType, GamePadBtnType�v
		// ��L�ȊO�̈����̌^�̏ꍇ�AInputManager���g�������͌��m�ɂȂ�
		template <class T>
		static bool isPush(T type);

		// ����̓��͂�������n�߂������n�߂�
		// �u�Ή�������́FMouseButtonType, KeybordKeyType, GamePadBtnType�v
		// ��L�ȊO�̈����̌^�̏ꍇ�AInputManager���g�������͌��m�ɂȂ�
		template <class T>
		static bool isTrigger(T type);

		// �ړ��������擾
		static const tktkMath::Vector2& moveVec();

		// ���_�ړ��������擾
		static const tktkMath::Vector2& lookVec();

		// �}�E�X�J�[�\���̍��W���擾����
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* �^�C���֌W�̏��� */
	public:

		// �o�ߎ��Ԃ�����������
		static void resetElapsedTime();

		// �O�t���[���Ƃ̎��Ԃ̍������߂�
		static float deltaTime();

		// �O�t���[���Ƃ̎��Ԃ̍������߂�iTimeScale�𖳎��j
		static float noScaleDeltaTime();

		// �v���O�������N�����Ă���̎��ԁi�b�j��Ԃ�
		static float getCurTimeSec();

		// �ő��deltaTime�̒l��ݒ�i���̐��j
		static void setMaximumDeltaTime(float maximumDeltaTime);

		// ���Ԃ̌o�ߑ��x�������擾����
		static float getTimeScale();

		// ���Ԃ̌o�ߑ��x������ݒ肷��i0.0�`float_max�j
		static void setTimeScale(float timeScaleRate);

		// ��ƂȂ�FPS��ݒ肷��
		static void setBaseFps(unsigned int baseFps = 60U);

		// ��ƂȂ�FPS���擾����
		static unsigned int getBaseFps();

		// �u�ԓI��FPS���擾����
		static float fps();

	//************************************************************
	/* ��e���v���[�g�֐� */
	private:

		static bool isPushImpl(int commandId);
		static bool isPushImpl(MouseButtonType buttonType);
		static bool isPushImpl(KeybordKeyType keyType);
		static bool isPushImpl(GamePadBtnType btnType);

		static bool isTriggerImpl(int commandId);
		static bool isTriggerImpl(MouseButtonType buttonType);
		static bool isTriggerImpl(KeybordKeyType keyType);
		static bool isTriggerImpl(GamePadBtnType btnType);
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// ID�ɑΉ��������͂�������Ă��邩�𔻒�
	template<class T>
	inline bool DX12Game::isPush(T type)
	{
		return isPushImpl(static_cast<int>(type));
	}

	// �w��̃}�E�X�{�^����������Ă��邩
	template<>
	inline bool DX12Game::isPush(MouseButtonType type)
	{
		return isPushImpl(type);
	}

	// �w��̃L�[��������Ă��邩�𔻒�
	template<>
	inline bool DX12Game::isPush(KeybordKeyType type)
	{
		return isPushImpl(type);
	}

	// �w��̃p�b�h�{�^����������Ă��邩�𔻒�
	template<>
	inline bool DX12Game::isPush(GamePadBtnType type)
	{
		return isPushImpl(type);
	}

	template<class T>
	inline bool DX12Game::isTrigger(T type)
	{
		return isTriggerImpl(static_cast<int>(type));
	}

	// �w��̃}�E�X�{�^����������n�߂����𔻒�
	template<>
	inline bool DX12Game::isTrigger(MouseButtonType type)
	{
		return isTriggerImpl(type);
	}

	// �w��̃L�[��������n�߂����𔻒�
	template<>
	inline bool DX12Game::isTrigger(KeybordKeyType type)
	{
		return isTriggerImpl(type);
	}

	// �w��̃p�b�h�{�^����������n�߂����𔻒�
	template<>
	inline bool DX12Game::isTrigger(GamePadBtnType type)
	{
		return isTriggerImpl(type);
	}
}
#endif // !TKTK_DX12_GAME_H_