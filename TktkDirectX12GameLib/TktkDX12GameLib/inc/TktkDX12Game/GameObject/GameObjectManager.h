#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <memory>
#include <forward_list>
#include "GameObjectPtr.h"
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
		void runHandleMessageAll(unsigned int messageId, const MessageAttachment& value);

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		GameObjectPtr findGameObjectWithTag(int tag) const;

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag) const;

	private:

		std::forward_list<std::shared_ptr<GameObject>> m_gameObjectList;
		std::forward_list<std::shared_ptr<GameObject>> m_newGameObjectList;
	};
}
#endif // !GAME_OBJECT_MANAGER_H_