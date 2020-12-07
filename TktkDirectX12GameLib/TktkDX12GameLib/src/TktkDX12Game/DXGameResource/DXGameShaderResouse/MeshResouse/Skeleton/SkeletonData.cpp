#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/SkeletonData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/Structs/SkeletonInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/Structs/MotionBoneParam.h"

namespace tktk
{
    SkeletonData::SkeletonData(const SkeletonInitParam& initParam)
    {
		// ���s��̔z��p�̃��������m�ۂ���
		m_boneMatrixArray.reserve(initParam.boneDataArray.size());

		// ���s��̔z��ƍ��̖��O�����т��邽�߂̔z���錾���A���������m�ۂ���
		std::vector<std::string> boneNameArray;
		boneNameArray.reserve(initParam.boneDataArray.size());

		// �����̍����̔z��̗v�f���������[�v����
		for (size_t i = 0; i < initParam.boneDataArray.size(); i++)
		{
			// ���݂̍����
			const auto& bonedata = initParam.boneDataArray.at(i);

			// ���s��̒l��z��ɒǉ�����
			m_boneMatrixArray.push_back(tktkMath::Matrix4_v::identity);

			// ���̖��O�̒l��z��ɒǉ�����
			boneNameArray.push_back(bonedata.boneName);

			// �{�[���̐e�q�Ǘ����Ǘ�����A�z�z��ɗv�f��ǉ�����
			m_boneNodeMap[bonedata.boneName].boneIndex = i;
			m_boneNodeMap[bonedata.boneName].startPos = bonedata.pos;
		}

		// �����̍����̔z��̗v�f���������[�v����
		for (const auto& node : initParam.boneDataArray)
		{
			// �e�̍�����\���l���s���������牽�����Ȃ�
			if (node.parentNo >= initParam.boneDataArray.size()) continue;

			// �e�̍��̖��O���擾����
			const auto& parentName = boneNameArray.at(node.parentNo);

			// �{�[���̐e�q�Ǘ����Ǘ�����A�z�z��̎q�v�f��\���z����X�V����
			m_boneNodeMap.at(parentName).children.emplace_back(&m_boneNodeMap.at(node.boneName));
		}
    }

	SkeletonData::SkeletonData(const SkeletonData& other)
		: m_boneMatrixArray(other.m_boneMatrixArray)
		, m_boneNodeMap(other.m_boneNodeMap)
	{
		// �R�s�[�����um_boneNodeMap�v���̃|�C���^���w�������A�h���X�𐳂�
		for (auto& writeboneNode : m_boneNodeMap)
		{
			for (auto& child : writeboneNode.second.children)
			{
				for (auto& readBoneNode : m_boneNodeMap)
				{
					if (child->boneIndex == readBoneNode.second.boneIndex)
					{
						child = &readBoneNode.second;
						break;
					}
				}
			}
		}
	}

	SkeletonData::SkeletonData(SkeletonData&& other) noexcept
		: m_boneMatrixArray(std::move(other.m_boneMatrixArray))
		, m_boneNodeMap(std::move(other.m_boneNodeMap))
	{
	}

	void SkeletonData::transform(const std::vector<MotionBoneParam>& transformMatrices)
	{
		// ���s���P�ʍs��ŏ���������
		std::fill(std::begin(m_boneMatrixArray), std::end(m_boneMatrixArray), tktkMath::Matrix4_v::identity);

		// �{�[�����̍��W�ϊ��s��̔z������񂷂�
		for (const auto& node : transformMatrices)
		{
			if (m_boneNodeMap.count(node.boneName) == 0U) continue;

			// �{�[���̖��O����{�[�������擾����
			const auto& boneNode = m_boneNodeMap.at(node.boneName);

			// �{�[�����ɍ��W�ϊ��s���ݒ肷��
			// �����W�ϊ����̌��_�̊֌W��A���X��₱����
			m_boneMatrixArray.at(boneNode.boneIndex)
				= tktkMath::Matrix4::createTranslation(-boneNode.startPos) 
				* node.transform
				* tktkMath::Matrix4::createTranslation(boneNode.startPos);
		}

		// �{�[���̐e�q�Ԃł̍��W�ϊ����s��
		if (m_boneNodeMap.count("�Z���^�[") != 0U)
		{
			transform(&m_boneNodeMap.at("�Z���^�["), tktkMath::Matrix4_v::identity);
		}
		else if (m_boneNodeMap.count("Hips") != 0U)
		{
			transform(&m_boneNodeMap.at("Hips"), tktkMath::Matrix4_v::identity);
		}
	}

	std::array<tktkMath::Matrix4, 128U> SkeletonData::getBoneMatrixArray() const
	{
		auto result = std::array<tktkMath::Matrix4, 128U>();

		// ���s��̏���l�����[�v����
		for (size_t i = 0; i < 128U; i++)
		{
			// ���s����Ō�܂ŏ�������ł����烋�[�v���I������
			if (i >= m_boneMatrixArray.size()) break;

			// ���s�����������
			result.at(i) = m_boneMatrixArray.at(i);
		}
		return result;
	}

	void SkeletonData::transform(const SkeletonData::BoneNode* boneNode, const tktkMath::Matrix4& transformMat)
	{
		// �����̍����ɑΉ����鍜�s��������̍s��ō��W�ϊ�����
		m_boneMatrixArray.at(boneNode->boneIndex) *= transformMat;
			
		// �����̍����̎q�v�f�̔z������񂷂�
		for (const SkeletonData::BoneNode* children : boneNode->children)
		{
			// �q�v�f�ƍ��W�ϊ��������s��������Ɏ��g���ċN�Ăяo������
			transform(children, m_boneMatrixArray.at(boneNode->boneIndex));
		}
	}
}