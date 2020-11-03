#ifndef GAME_OBJECT_TAG_LIST_H_
#define GAME_OBJECT_TAG_LIST_H_

#include <unordered_set>
#include "GameObjectTagCarrier.h"

namespace tktk
{
	// �Q�[���I�u�W�F�N�g�̃^�O���Ǘ�����R���e�i
	class GameObjectTagList
	{
	public:

		GameObjectTagList() = default;
		~GameObjectTagList() = default;

	public:

		// �����̃^�O��ǉ�����
		void addTag(GameObjectTagCarrier tag);

		// �����̃^�O���폜����
		void removeTag(GameObjectTagCarrier tag);

		// �����̃^�O���������Ă��邩�𔻒肷��
		bool contain(GameObjectTagCarrier tag) const;

	private:

		std::unordered_set<GameObjectTagCarrier> m_tags;
	};
}
#endif // !GAME_OBJECT_TAG_LIST_H_