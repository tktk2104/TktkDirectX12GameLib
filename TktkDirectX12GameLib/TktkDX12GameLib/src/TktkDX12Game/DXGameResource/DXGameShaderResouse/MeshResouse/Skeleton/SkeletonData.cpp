#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/SkeletonData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/Structs/SkeletonInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/Structs/MotionBoneParam.h"

namespace tktk
{
    SkeletonData::SkeletonData(const SkeletonInitParam& initParam)
    {
		// 骨行列の配列用のメモリを確保する
		m_boneMatrixArray.reserve(initParam.boneDataArray.size());

		// 骨行列の配列と骨の名前を結びつけるための配列を宣言し、メモリを確保する
		std::vector<std::string> boneNameArray;
		boneNameArray.reserve(initParam.boneDataArray.size());

		// 引数の骨情報の配列の要素数だけループする
		for (size_t i = 0; i < initParam.boneDataArray.size(); i++)
		{
			// 現在の骨情報
			const auto& bonedata = initParam.boneDataArray.at(i);

			// 骨行列の値を配列に追加する
			m_boneMatrixArray.push_back(tktkMath::Matrix4_v::identity);

			// 骨の名前の値を配列に追加する
			boneNameArray.push_back(bonedata.boneName);

			// ボーンの親子管理を管理する連想配列に要素を追加する
			m_boneNodeMap[bonedata.boneName].boneIndex = i;
			m_boneNodeMap[bonedata.boneName].startPos = bonedata.pos;
		}

		// 引数の骨情報の配列の要素数だけループする
		for (const auto& node : initParam.boneDataArray)
		{
			// 親の骨情報を表す値が不正だったら何もしない
			if (node.parentNo >= initParam.boneDataArray.size()) continue;

			// 親の骨の名前を取得する
			const auto& parentName = boneNameArray.at(node.parentNo);

			// ボーンの親子管理を管理する連想配列の子要素を表す配列を更新する
			m_boneNodeMap.at(parentName).children.emplace_back(&m_boneNodeMap.at(node.boneName));
		}
    }

	SkeletonData::SkeletonData(const SkeletonData& other)
		: m_boneMatrixArray(other.m_boneMatrixArray)
		, m_boneNodeMap(other.m_boneNodeMap)
	{
		// コピーした「m_boneNodeMap」内のポインタが指し示すアドレスを正す
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
		// 骨行列を単位行列で初期化する
		std::fill(std::begin(m_boneMatrixArray), std::end(m_boneMatrixArray), tktkMath::Matrix4_v::identity);

		// ボーン毎の座標変換行列の配列を巡回する
		for (const auto& node : transformMatrices)
		{
			if (m_boneNodeMap.count(node.boneName) == 0U) continue;

			// ボーンの名前からボーン情報を取得する
			const auto& boneNode = m_boneNodeMap.at(node.boneName);

			// ボーン情報に座標変換行列を設定する
			// ※座標変換時の原点の関係上、少々ややこしい
			m_boneMatrixArray.at(boneNode.boneIndex)
				= tktkMath::Matrix4::createTranslation(-boneNode.startPos) 
				* node.transform
				* tktkMath::Matrix4::createTranslation(boneNode.startPos);
		}

		// ボーンの親子間での座標変換を行う
		if (m_boneNodeMap.count("センター") != 0U)
		{
			transform(&m_boneNodeMap.at("センター"), tktkMath::Matrix4_v::identity);
		}
		else if (m_boneNodeMap.count("Hips") != 0U)
		{
			transform(&m_boneNodeMap.at("Hips"), tktkMath::Matrix4_v::identity);
		}
	}

	std::array<tktkMath::Matrix4, 128U> SkeletonData::getBoneMatrixArray() const
	{
		auto result = std::array<tktkMath::Matrix4, 128U>();

		// 骨行列の上限値分ループする
		for (size_t i = 0; i < 128U; i++)
		{
			// 骨行列を最後まで書き込んでいたらループを終了する
			if (i >= m_boneMatrixArray.size()) break;

			// 骨行列を書き込む
			result.at(i) = m_boneMatrixArray.at(i);
		}
		return result;
	}

	void SkeletonData::transform(const SkeletonData::BoneNode* boneNode, const tktkMath::Matrix4& transformMat)
	{
		// 引数の骨情報に対応する骨行列を引数の行列で座標変換する
		m_boneMatrixArray.at(boneNode->boneIndex) *= transformMat;
			
		// 引数の骨情報の子要素の配列を巡回する
		for (const SkeletonData::BoneNode* children : boneNode->children)
		{
			// 子要素と座標変換した骨行列を引数に自身を再起呼び出しする
			transform(children, m_boneMatrixArray.at(boneNode->boneIndex));
		}
	}
}