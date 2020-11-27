#include "Act3D_MainSceneChangerScript.h"

#include "../../../../Enums/Enums.h"

void Act3D_MainSceneChangerScript::start()
{
	m_fadeSprite = getComponent<tktk::SpriteDrawer>();

	if (m_fadeSprite.expired())
	{
		throw std::runtime_error("Act3D_MainSceneChanger not found SpriteDrawer");
	}
}

void Act3D_MainSceneChangerScript::update()
{
	// �^�C�}�[���X�V����
	m_sceneChangeSecTimer += tktk::DX12Game::deltaTime();

	// �V�[���J�ڂ��I����Ă�����
	if (m_endSceneChange)
	{
		// �t�F�[�h�p�X�v���C�g�����X�ɔ�������
		const auto& curBlendRate = m_fadeSprite->getBlendRate();
		m_fadeSprite->setBlendRate(curBlendRate - tktkMath::Color(0.0f, (1.0f / 2.0f) * tktk::DX12Game::deltaTime()));

		// ���g���E�����ԂɂȂ��Ă�����
		if (m_sceneChangeSecTimer > SelfDeadTime)
		{
			getGameObject()->destroy();
			return;
		}

		return;
	}

	// �t�F�[�h�p�X�v���C�g�����X�ɔZ������
	const auto& curBlendRate = m_fadeSprite->getBlendRate();
	m_fadeSprite->setBlendRate(curBlendRate + tktkMath::Color(0.0f, (1.0f / 2.0f) * tktk::DX12Game::deltaTime()));

	// �V�[����J�ڂ����鎞�ԂɂȂ��Ă�����
	if (m_sceneChangeSecTimer > SceneChangeTime)
	{
		// ���C���V�[���𖳌�������
		tktk::DX12Game::disableScene(SceneId::Main);

		// ���U���g�V�[����L���ɂ���
		tktk::DX12Game::enableScene(SceneId::Result);

		// �V�[���J�ڂ��I������t���O�𗧂Ă�
		m_endSceneChange = true;
	}
}
