#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

/* funcUseType */
#include "../../GameObjectResouse/GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	class SceneInstanceCarrier;
	struct SceneInitParam;

	// �V�[���Ǘ��N���X
	class SceneManager
	{
	public:

		explicit SceneManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~SceneManager();

	public:

		// �V�[�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const SceneInitParam& initParam);

		// �V�[���̏I�����ɍ폜����Q�[���I�u�W�F�N�g�^�O��ݒ肷��
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// �V�[����L���ɂ���
		void enable(size_t handle);

		// �V�[���𖳌��ɂ���
		void disable(size_t handle);

		// �V�[���̍X�V����
		void update();

	private:

		tktkContainer::ResourceContainer<SceneInstanceCarrier> m_sceneArray;
	};
}
#endif // !SCENE_MANAGER_H_