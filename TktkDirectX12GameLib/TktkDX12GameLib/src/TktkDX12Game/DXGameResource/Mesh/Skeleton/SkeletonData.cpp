#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/SkeletonData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/Skeleton/BoneMatrixCbufferData.h"

namespace tktk
{
    SkeletonData::SkeletonData(const SkeletonInitParam& initParam)
    {
		m_boneMatrixArray.reserve(initParam.boneDataArray.size());

		std::vector<std::string> boneNameArray;
		boneNameArray.reserve(initParam.boneDataArray.size());

		for (unsigned int i = 0; i < initParam.boneDataArray.size(); i++)
		{
			const auto& bonedata = initParam.boneDataArray.at(i);

			m_boneMatrixArray.push_back(tktkMath::Matrix4_v::identity);
			boneNameArray.push_back(bonedata.boneName);

			m_boneNodeMap[bonedata.boneName].boneIndex = i;
			m_boneNodeMap[bonedata.boneName].startPos = bonedata.pos;
		}

		for (auto& node : initParam.boneDataArray)
		{
			if (node.parentNo >= initParam.boneDataArray.size()) continue;

			auto parentName = boneNameArray.at(node.parentNo);

			m_boneNodeMap.at(parentName).children.emplace_back(&m_boneNodeMap.at(node.boneName));
		}
    }

	void SkeletonData::transform(const std::vector<MotionBoneParam>& transformMatrices)
	{
		std::fill(std::begin(m_boneMatrixArray), std::end(m_boneMatrixArray), tktkMath::Matrix4_v::identity);

		for (const auto& node : transformMatrices)
		{
			const auto& boneNode = m_boneNodeMap.at(node.boneName);

			m_boneMatrixArray.at(boneNode.boneIndex)
				= tktkMath::Matrix4::createTranslation(-boneNode.startPos) 
				* node.transform
				* tktkMath::Matrix4::createTranslation(boneNode.startPos);
		}

		// ボーンの親子間での座標変換を行う
		transform(&m_boneNodeMap.at("センター"), tktkMath::Matrix4_v::identity);
	}

	void SkeletonData::updateBoneMatrixCbuffer() const
	{
		BoneMatrixCbufferData boneMatBuf;

		for (unsigned int i = 0; i < 128U; i++)
		{
			if (i >= m_boneMatrixArray.size()) break;
			boneMatBuf.boneMatrix[i] = m_boneMatrixArray.at(i);
		}
		DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::BoneMatCbuffer), boneMatBuf);
	}

	void SkeletonData::transform(const SkeletonData::BoneNode* boneNode, const tktkMath::Matrix4& transformMat)
	{
		m_boneMatrixArray.at(boneNode->boneIndex) *= transformMat;
			
		for (const SkeletonData::BoneNode* children : boneNode->children)
		{
			transform(children, m_boneMatrixArray.at(boneNode->boneIndex));
		}
	}
}