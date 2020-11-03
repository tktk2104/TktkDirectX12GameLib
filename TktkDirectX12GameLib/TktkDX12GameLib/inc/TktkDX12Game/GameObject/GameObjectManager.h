#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <memory>
#include <forward_list>
#include "GameObjectPtr.h"
#include "GameObjectTagCarrier.h"
#include "../EventMessage/MessageTypeCarrier.h"
#include "../EventMessage/MessageAttachment.h"


namespace tktk
{
	class GameObject;

	// �Q�[���I�u�W�F�N�g�Ǘ��N���X
	class GameObjectManager
	{
	public:

		GameObjectManager() = default;

	public:

		void update();

		// �O�t���[���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// ���񂾃Q�[���I�u�W�F�N�g���폜����
		void removeDeadObject();

	public:

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		void runHandleMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment);

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�č폜����
		void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	private:

		std::forward_list<std::shared_ptr<GameObject>> m_gameObjectList;
		std::forward_list<std::shared_ptr<GameObject>> m_newGameObjectList;
	};
}
#endif // !GAME_OBJECT_MANAGER_H_