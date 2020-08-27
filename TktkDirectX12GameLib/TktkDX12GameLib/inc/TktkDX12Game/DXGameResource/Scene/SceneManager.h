#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SceneInstanceCarrier.h"

namespace tktk
{
	// �V�[���Ǘ��N���X
	class SceneManager
	{
	public:

		explicit SceneManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SceneManager() = default;

	public:

		// �V�[�������A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);

		// �V�[����L���ɂ���
		void enable(unsigned int handle);

		// �V�[���𖳌��ɂ���
		void disable(unsigned int handle);

		// �V�[���̍X�V����
		void update();

	private:

		tktkContainer::ResourceContainer<SceneInstanceCarrier> m_sceneArray;
	};
}
#endif // !SCENE_MANAGER_H_