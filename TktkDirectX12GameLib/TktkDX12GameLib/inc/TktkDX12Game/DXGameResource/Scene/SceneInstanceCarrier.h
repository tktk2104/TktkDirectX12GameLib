#ifndef SCENE_INSTANCE_CARRIER_H_
#define SCENE_INSTANCE_CARRIER_H_

#include "SceneVTable.h"
#include "../../GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	// �V�[���̃C���X�^���X��ێ�����N���X
	class SceneInstanceCarrier
	{
	public:

		SceneInstanceCarrier(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);
		~SceneInstanceCarrier();

		// ���[�u�R���X�g���N�^
		SceneInstanceCarrier(SceneInstanceCarrier&& other) noexcept;

	public:

		// �V�[���̏I�����ɍ폜����Q�[���I�u�W�F�N�g�^�O��ݒ肷��
		void setSceneEndDestroyGameObjectTag(GameObjectTagCarrier tag);

		// �V�[����L���ɂ���
		void enable();

		// �V�[���𖳌��ɂ���
		void disable();

		// �V�[�����L���A������Ԃ�؂�ւ���
		void changeActive();

		// �V�[���̍X�V����
		void update();

	private:

		bool									m_isActive					{ false };
		bool									m_nextFrameIsActive			{ false };
		bool									m_runAfterChangeActiveFunc	{ false };
		std::unique_ptr<GameObjectTagCarrier>	m_destroyGameObjectTag		{ nullptr };
		std::shared_ptr<SceneBase>				m_scenePtr					{ nullptr };
		SceneVTable*							m_vtablePtr					{ nullptr };
	};
}
#endif // !SCENE_INSTANCE_CARRIER_H_