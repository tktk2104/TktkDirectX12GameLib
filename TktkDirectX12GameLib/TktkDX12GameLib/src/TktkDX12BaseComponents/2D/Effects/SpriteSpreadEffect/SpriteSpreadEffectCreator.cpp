#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/SpriteSpreadEffectCreator.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

#include "TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h"
#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h"
#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/Particle/SpriteSpreadEffectParticle.h"

namespace tktk
{
	SpriteSpreadEffectCreator::SpriteSpreadEffectCreator(const SpriteSpreadEffectParam& param)
		: m_param(param)
		, m_generateIntervalSecTimer(m_param.firstGenerateTimeSec)
	{
	}

	void SpriteSpreadEffectCreator::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteSpreadEffectCreator not found Transform2D");
		}
	}

	void SpriteSpreadEffectCreator::onEnable()
	{
		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g����ݒ�̏ꍇ�A
		if (m_param.changeAvtiveToReset)
		{
			// �����󋵂����Z�b�g����
			m_generateIntervalSecTimer = m_param.firstGenerateTimeSec;
			m_totalGenerateCounter = 0;
		}
	}

	void SpriteSpreadEffectCreator::update()
	{
		// ��������ɒB���Ă����琶�����Ȃ�
		if (m_param.totalGenerateNum > 0 && m_totalGenerateCounter == m_param.totalGenerateNum) return;

		if (m_generateIntervalSecTimer < 0.0f)
		{
			// ���������������[�v����
			auto generateNumRandomRange = tktkMath::Random::getRandI(-m_param.generateNumPerOnceRandomRange, m_param.generateNumPerOnceRandomRange);
			for (int i = 0; i < (m_param.generateNumPerOnce + generateNumRandomRange); i++)
			{
				// �p�[�e�B�N���I�u�W�F�N�g�����
				auto particleObject = DX12GameManager::createGameObject();

				// �������W���v�Z����
				auto generateLocalPosRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.generateLocalPosRandomRange.x, m_param.generateLocalPosRandomRange.x),
					tktkMath::Random::getRandF(-m_param.generateLocalPosRandomRange.y, m_param.generateLocalPosRandomRange.y)
				);
				auto generatePos = m_param.generateLocalPos + generateLocalPosRandomRange;

				//  �q�v�f�ǉ��t���O�������Ă��Ȃ������烏�[���h��Ԃł̍��W�ɂȂ�悤�ɏC������
				if (!m_param.setChild) generatePos = generatePos * m_transform->calculateWorldMatrix();

				// �W���o�����b�N�ɒ��ӂ��Ȃ����]�������
				auto rotate = tktkMath::Random::getRandF(m_param.minGenerateAngleDeg, m_param.maxGenerateAngleDeg);

				// �X�P�[�����v�Z����
				auto spriteScaleRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.x, m_param.spriteScaleRandomRange.x),
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.y, m_param.spriteScaleRandomRange.y)
				);

				// ���W�Ǘ��R���|�[�l���g�����
				Transform2DMaker::makeStart(particleObject)
					.initPosition(generatePos)
					.initRotationDeg(rotate)
					.initScaleRate(m_param.spriteScale + spriteScaleRandomRange)
					.create();

				// �X�v���C�g�`��R���|�[�l���g�����
				SpriteDrawerMaker::makeStart(particleObject)
					.spriteMaterialHandle(m_param.useSpriteHandle)
					.blendRate(m_param.spriteBlendRate)
					.create();

				// �X�v���C�g�p�[�e�B�N���p�̃R���|�[�l���g�����
				auto moveSpeedPerSecRandomRange = tktkMath::Random::getRandF(-m_param.moveSpeedPerSecRandomRange, m_param.moveSpeedPerSecRandomRange);
				auto lifeTimeSecRandomRange		= tktkMath::Random::getRandF(-m_param.lifeTimeSecRandomRange, m_param.lifeTimeSecRandomRange);
				particleObject->createComponent<SpriteSpreadEffectParticle>(
					m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange,
					m_param.lifeTimeSec + lifeTimeSecRandomRange
					);

				// �q�v�f�ǉ��t���O�������Ă�����q�v�f�ɒǉ�����
				if (m_param.setChild) getGameObject()->addChild(particleObject);

				// �������J�E���^���C���N�������g����
				++m_totalGenerateCounter;

				// ��������ɒB�����琶���𒆒f����
				if (m_param.totalGenerateNum > 0 && m_totalGenerateCounter == m_param.totalGenerateNum) break;
			}

			// �����ɂ��U�ꕝ���l�����Đ����Ԋu�^�C�}�[���Đݒ肷��
			auto intervalTimeRandomRange = tktkMath::Random::getRandF(-m_param.generateIntervalTimeRandomRange, m_param.generateIntervalTimeRandomRange);
			m_generateIntervalSecTimer = m_param.generateIntervalTimeSec + intervalTimeRandomRange;
			return;
		}

		// �����Ԋu�^�C�}�[���X�V
		m_generateIntervalSecTimer -= DX12GameManager::deltaTime();
	}
}