#include "Act3D_TitleSceneChangerScript.h"

#include "../../../../Enums/Enums.h"

void Act3D_TitleSceneChangerScript::start()
{
	m_soundPlayer = getComponent<tktk::SoundPlayer>();

	if (m_soundPlayer.expired())
	{
		throw std::runtime_error("Act3D_TitleSceneChangerScript not found SoundPlayer");
	}
}

void Act3D_TitleSceneChangerScript::update()
{
	// �V�[���J�ڂ��n�܂��Ă�����
	if (m_startSceneChange)
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

		if (m_sceneChangeSecTimer > SceneChangeTime)
		{
			// �^�C�g���V�[���𖳌�������
			tktk::DX12Game::disableScene(SceneId::Title);

			// ���C���V�[����L���ɂ���
			tktk::DX12Game::enableScene(SceneId::Main);

			// �V�[���J�ڂ��I������t���O�𗧂Ă�
			m_endSceneChange = true;
		}

		return;
	}

	// �����ꂩ�̓��͂���������
	if (tktk::DX12Game::isTrigger(CommandId::Any))
	{
		// �T�E���h���Đ�����
		m_soundPlayer->playSound();

		// �V�[���J�ڂ��J�n����
		m_startSceneChange = true;

		// �t�F�[�h�p�X�v���C�g
		m_fadeSprite = tktk::SpriteDrawerMaker::makeStart(getGameObject())
			.drawPriority(10)
			.spriteMaterialId(SpriteId::Black4x4)
			.blendRate({ 1.0f, 0.0f })
			.create();
	}
}
