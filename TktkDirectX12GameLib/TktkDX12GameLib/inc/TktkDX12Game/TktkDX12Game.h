#ifndef TKTK_DX12_GAME_H_
#define TKTK_DX12_GAME_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "_MainManager/DX12GameManager.h"

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
		template <class SceneType>
		static void enableScene(SceneType id);

		// �V�[���𖳌��ɂ���
		template <class SceneType>
		static void disableScene(SceneType id);

	//************************************************************
	/* �Q�[���I�u�W�F�N�g�̏��� */
	public:

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		template <class MessageIdType>
		static void sendMessageAll(MessageIdType messageId, const MessageAttachment& value = {});

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		static GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		template <class GameObjectTagType>
		static GameObjectPtr findGameObjectWithTag(GameObjectTagType tag);

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		template <class GameObjectTagType>
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagType tag);

	//************************************************************
	/* �}�E�X���͊֌W�̏��� */
	public:

		// �w��̃{�^����������Ă��邩
		static bool isPush(MouseButtonType buttonType);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(MouseButtonType buttonType);

		// �}�E�X�J�[�\���̍��W���擾����
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* �L�[�{�[�h���͊֌W�̏��� */
	public:

		// �w��̃L�[��������Ă��邩�𔻒�
		static bool isPush(KeybordKeyType keyType);

		// �w��̃L�[��������n�߂����𔻒�
		static bool isTrigger(KeybordKeyType keyType);

	//************************************************************
	/* �Q�[���p�b�h���͊֌W�̏��� */
	public:

		// ���X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getLstick();

		// �E�X�e�B�b�N�̌X�����擾�i-1.0�`1.0�̊ԁj
		static tktkMath::Vector2 getRstick();

		// �w��̃{�^����������Ă��邩�𔻒�
		static bool isPush(GamePadBtnType buttonType);

		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(GamePadBtnType buttonType);

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

		static void enableSceneImpl(unsigned int id);
		static void disableSceneImpl(unsigned int id);
		static void sendMessageAllImpl(unsigned int messageId, const MessageAttachment& value);
		static GameObjectPtr findGameObjectWithTagImpl(int tag);
		static std::forward_list<GameObjectPtr> findGameObjectsWithTagImpl(int tag);
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �V�[����L���ɂ���
	template<class SceneType>
	inline void DX12Game::enableScene(SceneType id)
	{
		enableSceneImpl(static_cast<unsigned int>(id));
	}

	// �V�[���𖳌��ɂ���
	template<class SceneType>
	inline void DX12Game::disableScene(SceneType id)
	{
		disableSceneImpl(static_cast<unsigned int>(id));
	}

	// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
	template<class MessageIdType>
	inline void DX12Game::sendMessageAll(MessageIdType messageId, const MessageAttachment& value)
	{
		sendMessageAllImpl(static_cast<unsigned int>(messageId), value);
	}

	// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
	// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
	template<class GameObjectTagType>
	inline GameObjectPtr DX12Game::findGameObjectWithTag(GameObjectTagType tag)
	{
		return findGameObjectWithTagImpl(static_cast<int>(tag));
	}

	// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
	template<class GameObjectTagType>
	inline std::forward_list<GameObjectPtr> DX12Game::findGameObjectsWithTag(GameObjectTagType tag)
	{
		return findGameObjectsWithTagImpl(static_cast<int>(tag));
	}
}
#endif // !TKTK_DX12_GAME_H_