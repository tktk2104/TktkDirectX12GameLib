#include "TktkDX12BaseComponents/2D/Effects/SpriteShrinkEffect/SpriteShrinkEffectCreator.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

#include "TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h"
#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h"
#include "TktkDX12BaseComponents/2D/SpriteAnimator/SpriteAnimatorMaker.h"
#include "TktkDX12BaseComponents/2D/Effects/SpriteShrinkEffect/Particle/SpriteShrinkEffectParticle.h"

namespace tktk
{
	SpriteShrinkEffectCreator::SpriteShrinkEffectCreator(const SpriteShrinkEffectParam& param)
		: m_param(param)
		, m_generateIntervalSecTimer(m_param.firstGenerateTimeSec)
	{
	}

	void SpriteShrinkEffectCreator::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteShrinkEffectCreator not found Transform2D");
		}

		// �p�[�e�B�N���I�u�W�F�N�g�����
		m_particleObject = DX12GameManager::createGameObject();

		// ���W�Ǘ��R���|�[�l���g�����
		Transform2DMaker::makeStart(m_particleObject)
			.create();

		// �q�v�f�ǉ��t���O�������Ă�����q�v�f�ɒǉ�����
		if (m_param.setChild) getGameObject()->addChild(m_particleObject);
	}

	void SpriteShrinkEffectCreator::onEnable()
	{
		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g����ݒ�̏ꍇ�A
		if (m_param.changeAvtiveToReset)
		{
			// �����󋵂����Z�b�g����
			m_generateIntervalSecTimer = m_param.firstGenerateTimeSec;
			m_totalGenerateCounter = 0;
		}
	}

	void SpriteShrinkEffectCreator::update()
	{
		// ��������ɒB���Ă����琶�����Ȃ�
		if (m_param.totalGenerateNum > 0 && m_totalGenerateCounter == m_param.totalGenerateNum) return;

		if (m_generateIntervalSecTimer < 0.0f)
		{
			// ���������������[�v����
			auto generateNumRandomRange = tktkMath::Random::getRandI(-m_param.generateNumPerOnceRandomRange, m_param.generateNumPerOnceRandomRange);
			for (int i = 0; i < (m_param.generateNumPerOnce + generateNumRandomRange); i++)
			{
				// ��]�������
				auto rotate = tktkMath::Random::getRandF(0.0f, 360.0f);

				// �X�P�[�����v�Z����
				auto spriteScaleRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.x, m_param.spriteScaleRandomRange.x),
					tktkMath::Random::getRandF(-m_param.spriteScaleRandomRange.y, m_param.spriteScaleRandomRange.y)
				);

				// ���k�_���W���v�Z����
				auto shrinkTargetPosRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.shrinkTargetPosRandomRange.x, m_param.shrinkTargetPosRandomRange.x),
					tktkMath::Random::getRandF(-m_param.shrinkTargetPosRandomRange.y, m_param.shrinkTargetPosRandomRange.y)
				);
				auto shrinkTargetPos = m_param.shrinkTargetPos + shrinkTargetPosRandomRange;

				//  �q�v�f�ǉ��t���O�������Ă��Ȃ������烏�[���h��Ԃł̍��W�ɂȂ�悤�ɏC������
				if (!m_param.setChild) shrinkTargetPos = shrinkTargetPos * m_transform->calculateWorldMatrix();

				auto moveSpeedPerSecRandomRange = tktkMath::Random::getRandF(-m_param.moveSpeedPerSecRandomRange, m_param.moveSpeedPerSecRandomRange);
				auto lifeTimeSecRandomRange = tktkMath::Random::getRandF(-m_param.lifeTimeSecRandomRange, m_param.lifeTimeSecRandomRange);

				// �������W���v�Z����
				auto generatePos = shrinkTargetPos - (tktkMath::Matrix3::createRotation(rotate).calculateUp() * (m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange) * (m_param.lifeTimeSec + lifeTimeSecRandomRange));

				// �X�v���C�g�`��R���|�[�l���g�����
				auto spriteDrawer = SpriteDrawerMaker::makeStart(m_particleObject)
					.spriteMaterialHandle(m_param.useSpriteHandle)
					.blendRate(m_param.spriteBlendRate)
					.localPosition(generatePos)
					.localRotationDeg(rotate)
					.localScaleRate(m_param.spriteScale + spriteScaleRandomRange)
					.create();

				// �A�j���[�V�������g�p����ݒ肾������
				if (m_param.useAnimation)
				{
					SpriteAnimatorMaker::makeStart(m_particleObject)
						.targetDrawer(spriteDrawer)
						.isLoop(m_param.isLoop)
						.initFrame(m_param.initFrame)
						.animSpeedRate(m_param.animSpeedRate)
						.animFramePerSec(m_param.animFramePerSec)
						.totalAnimFrameSize(m_param.totalAnimFrameSize)
						.create();
				}

				// �X�v���C�g�p�[�e�B�N���p�̃R���|�[�l���g�����
				auto scalingSizePerSecRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.scalingSizePerSecRandomRange.x, m_param.scalingSizePerSecRandomRange.x),
					tktkMath::Random::getRandF(-m_param.scalingSizePerSecRandomRange.y, m_param.scalingSizePerSecRandomRange.y)
				);
				m_particleObject->createComponent<SpriteShrinkEffectParticle>(
					spriteDrawer,
					m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange,
					m_param.scalingSizePerSec + scalingSizePerSecRandomRange,
					m_param.blendRateChangeWidthPerSec,
					m_param.lifeTimeSec + lifeTimeSecRandomRange
					);

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