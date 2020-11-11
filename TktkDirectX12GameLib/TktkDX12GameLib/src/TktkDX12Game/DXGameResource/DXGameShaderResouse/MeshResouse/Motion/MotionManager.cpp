#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionManager.h"

#include <TktkMath/Structs/Matrix4.h>
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionBoneParam.h"

namespace tktk
{
	MotionManager::MotionManager(const tktkContainer::ResourceContainerInitParam& initParam)
		: m_motionArray(initParam)
	{
	}

	// �f�X�g���N�^���C�����C��������
	MotionManager::~MotionManager() = default;

	size_t MotionManager::load(const std::string& motionFileName)
	{
		return m_motionArray.create(motionFileName);
	}

	size_t MotionManager::getEndFrameNo(size_t handle) const
	{
		return m_motionArray.getMatchHandlePtr(handle)->getEndFrameNo();
	}

	std::vector<MotionBoneParam> MotionManager::calculateBoneTransformMatrices(size_t curHandle, size_t preHandle, size_t curFrame, size_t preFrame, float amount) const
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
		for (size_t i = 0; i < curMatrices.size(); i++)
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