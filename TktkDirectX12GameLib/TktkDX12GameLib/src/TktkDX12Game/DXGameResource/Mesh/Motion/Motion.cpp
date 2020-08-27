#include "TktkDX12Game/DXGameResource/Mesh/Motion/Motion.h"

namespace tktk
{
	Motion::Motion(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_motionArray(initParam)
	{
	}

	unsigned int Motion::load(const std::string& motionFileName)
	{
		return m_motionArray.create(motionFileName);
	}

	unsigned int Motion::getEndFrameNo(unsigned int handle) const
	{
		return m_motionArray.getMatchHandlePtr(handle)->getEndFrameNo();
	}

	std::vector<MotionBoneParam> Motion::calculateBoneTransformMatrices(unsigned int curHandle, unsigned int preHandle, unsigned int curFrame, unsigned int preFrame, float amount) const
	{
		// ���̃t���[���Ŏg�p���Ă������[�V�����̍��W�ϊ��s��z����擾����
		auto curMatrices = m_motionArray.getMatchHandlePtr(curHandle)->calculateBoneTransformMatrices(curFrame);

		// �O�t���[���ƕω����S��������Ύ擾�������t���[���������̂܂ܕԂ�
		if (preHandle == curHandle && preFrame == curFrame) return curMatrices;

		// ���[�V�����̕⊮�������P�ȏゾ�����獡�t���[���������̂܂ܕԂ�
		if (amount >= 1.0f) return curMatrices;

		// �O�̃t���[���Ŏg�p���Ă������[�V�����̍��W�ϊ��s��z����擾����
		auto preMatrices = m_motionArray.getMatchHandlePtr(preHandle)->calculateBoneTransformMatrices(preFrame);

		// ���W�ϊ��z��̕⊮���ʂ̒l
		std::vector<MotionBoneParam> result;
		result.reserve(curMatrices.size());

		// ���[�V�����̍��W�ϊ��s��z������񂷂�
		for (unsigned int i = 0; i < curMatrices.size(); i++)
		{
			MotionBoneParam boneParam{};

			// �Ώۂ̃{�[���̖��̂�ݒ�
			boneParam.boneName = curMatrices.at(i).boneName;

			// �O�t���[���ƍ��t���[���̍��W�ϊ��s�����`�⊮����
			boneParam.transform = tktkMath::Matrix4::lerp(
				preMatrices.at(i).transform,
				curMatrices.at(i).transform,
				amount
			);

			// �v�Z�������W�ϊ��s���z��ɒǉ�
			result.push_back(boneParam);
		}

		// �v�Z���ʂ�Ԃ�
		return result;
	}
}