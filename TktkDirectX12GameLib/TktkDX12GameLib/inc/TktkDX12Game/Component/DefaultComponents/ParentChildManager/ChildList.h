#ifndef CHILD_LIST_H_
#define CHILD_LIST_H_

#include <forward_list>
#include "../../../GameObject/GameObjectPtr.h"
#include "../../../EventMessage/MessageAttachment.h"

namespace tktk
{
	// �q�v�f�̃��X�g
	class ChildList
	{
	public:

		ChildList() = default;
		~ChildList() {}

	public:

		// �V���Ȏq�v�f��ǉ�
		// ���ǉ������q�v�f�͎��̃t���[���Ń��C���̃��X�g�ɒǉ������
		void addChild(const GameObjectPtr& child);

		// �q�v�f�̃��X�g���擾
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// ���g�̎q�v�f��������̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		GameObjectPtr findGameObjectWithTag(int tag) const;

		// ���g�̎q�v�f��������̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag) const;

		// �O�t���[���ɒǉ����ꂽ�Q�[���I�u�W�F�N�g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// ���S�t���O�������Ă���Q�[���I�u�W�F�N�g���폜����
		void removeDeadComponent();

		// �w��̎q�v�f�����X�g����폜����
		void remove(const GameObjectPtr& gameObject);

		// �S�Ă̎q�v�f���E��
		void destroyAll();

		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(unsigned int messageId, const MessageAttachment& value);

	private:

		std::forward_list<GameObjectPtr> m_childList;
		std::forward_list<GameObjectPtr> m_newGameObjectList;
	};
}
#endif // !CHILD_LIST_H_