#include "TktkDX12BaseComponents/3D/Effects/BillboardShrinkEffect/BillboardShrinkEffectCreator.h"

#include <stdexcept>
#include <TktkMath/Random.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

#include "TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h"
#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawerMaker.h"
#include "TktkDX12BaseComponents/3D/Effects/BillboardShrinkEffect/Particle/BillboardShrinkEffectParticle.h"

namespace tktk
{
	BillboardShrinkEffectCreator::BillboardShrinkEffectCreator(const BillboardShrinkEffectParam& param)
		: m_param(param)
		, m_generateIntervalSecTimer(m_param.firstGenerateTimeSec)
	{
	}

	void BillboardShrinkEffectCreator::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("BillboardShrinkEffectCreator not found Transform3D");
		}
	}

	void BillboardShrinkEffectCreator::onEnable()
	{
		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g����ݒ�̏ꍇ�A
		if (m_param.changeAvtiveToReset)
		{
			// �����󋵂����Z�b�g����
			m_generateIntervalSecTimer = m_param.firstGenerateTimeSec;
			m_totalGenerateCounter = 0;
		}
	}

	void BillboardShrinkEffectCreator::update()
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

				// �r���{�[�h�p�[�e�B�N���p�̃R���|�[�l���g�����
				auto moveSpeedPerSecRandomRange = tktkMath::Random::getRandF(-m_param.moveSpeedPerSecRandomRange, m_param.moveSpeedPerSecRandomRange);
				auto lifeTimeSecRandomRange = tktkMath::Random::getRandF(-m_param.lifeTimeSecRandomRange, m_param.lifeTimeSecRandomRange);
				particleObject->createComponent<BillboardShrinkEffectParticle>(
					m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange,
					m_param.lifeTimeSec + lifeTimeSecRandomRange
					);

				// �W���o�����b�N�ɒ��ӂ��Ȃ����]�������
				auto rotate = tktkMath::Quaternion::createFromEulerAngle({ tktkMath::Random::getRandF(0.0f, 360.0f), 0.0f, 0.0f})
					* tktkMath::Quaternion::createFromEulerAngle({ 0.0f, tktkMath::Random::getRandF(0.0f, 360.0f),  0.0f });

				// �X�P�[�����v�Z����
				auto billboardScaleRandomRange = tktkMath::Vector2(
					tktkMath::Random::getRandF(-m_param.billboardScaleRandomRange.x, m_param.billboardScaleRandomRange.x),
					tktkMath::Random::getRandF(-m_param.billboardScaleRandomRange.y, m_param.billboardScaleRandomRange.y)
				);
				auto billboardScale = m_param.billboardScale + billboardScaleRandomRange;

				// ���k�_���W���v�Z����
				auto shrinkTargetPosRandomRange = tktkMath::Vector3(
					tktkMath::Random::getRandF(-m_param.shrinkTargetPosRandomRange.x, m_param.shrinkTargetPosRandomRange.x),
					tktkMath::Random::getRandF(-m_param.shrinkTargetPosRandomRange.y, m_param.shrinkTargetPosRandomRange.y),
					tktkMath::Random::getRandF(-m_param.shrinkTargetPosRandomRange.z, m_param.shrinkTargetPosRandomRange.z)
				);
				auto shrinkTargetPos = m_param.shrinkTargetPos + shrinkTargetPosRandomRange;

				//  �q�v�f�ǉ��t���O�������Ă��Ȃ������烏�[���h��Ԃł̍��W�ɂȂ�悤�ɏC������
				if (!m_param.setChild) shrinkTargetPos = shrinkTargetPos * m_transform->calculateWorldMatrix();

				// �������W���v�Z����
				auto generatePos = shrinkTargetPos - (tktkMath::Matrix4::createFromQuaternion(rotate).calculateForwardLH() * (m_param.moveSpeedPerSec + moveSpeedPerSecRandomRange) * (m_param.lifeTimeSec + lifeTimeSecRandomRange));

				// ���W�Ǘ��R���|�[�l���g�����
				Transform3DMaker::makeStart(particleObject)
					.initPosition(generatePos)
					.initRotation(rotate)
					.initScaleRate({ billboardScale.x, billboardScale.y, 1.0f })
					.create();

				// �r���{�[�h�`��R���|�[�l���g�����
				BillboardDrawerMaker::makeStart(particleObject)
					.billboardMaterialHandle(m_param.useBillboardHandle)
					.notClippingUseHandle(m_param.useBillboardHandle)
					.blendRate(m_param.billboardBlendRate)
					.create();

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