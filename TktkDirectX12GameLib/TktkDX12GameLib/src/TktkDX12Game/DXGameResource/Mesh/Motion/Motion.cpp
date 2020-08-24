#include "TktkDX12Game/DXGameResource/Mesh/Motion/Motion.h"

namespace tktk
{
	Motion::Motion(unsigned int motionNum)
		: m_motionArray(motionNum)
	{
	}

	void Motion::load(unsigned int id, const std::string& motionFileName)
	{
		m_motionArray.emplaceAt(id, motionFileName);
	}

	unsigned int Motion::getEndFrameNo(unsigned int id) const
	{
		return m_motionArray.at(id)->getEndFrameNo();
	}

	std::vector<MotionBoneParam> Motion::calculateBoneTransformMatrices(unsigned int curId, unsigned int preId, unsigned int curFrame, unsigned int preFrame, float amount) const
	{
		// ���̃t���[���Ŏg�p���Ă������[�V�����̍��W�ϊ��s��z����擾����
		auto curMatrices = m_motionArray.at(curId)->calculateBoneTransformMatrices(curFrame);

		// �O�t���[���ƕω����S��������Ύ擾�������t���[���������̂܂ܕԂ�
		if (preId == curId && preFrame == curFrame) return curMatrices;

		// ���[�V�����̕⊮�������P�ȏゾ�����獡�t���[���������̂܂ܕԂ�
		if (amount >= 1.0f) return curMatrices;

		// �O�̃t���[���Ŏg�p���Ă������[�V�����̍��W�ϊ��s��z����擾����
		auto preMatrices = m_motionArray.at(preId)->calculateBoneTransformMatrices(preFrame);

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