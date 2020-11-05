#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "SceneInstanceCarrier.h"
#include "SceneDataInitParam.h"
#include "../../GameObject/GameObjectTagCarrier.h"

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
		size_t create(const SceneDataInitParam& initParam);

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