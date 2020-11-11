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

	// デストラクタを非インライン化する
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
		// 今のフレームで使用していたモーションの座標変換行列配列を取得する
		auto curMatrices = m_motionArray.getMatchHandlePtr(curHandle)->calculateBoneTransformMatrices(curFrame);

		// 前フレームと変化が全く無ければ取得した今フレーム情報をそのまま返す
		if (preHandle == curHandle && preFrame == curFrame) return curMatrices;

		// モーションの補完割合が１以上だったら今フレーム情報をそのまま返す
		if (amount >= 1.0f) return curMatrices;

		// 前のフレームで使用していたモーションの座標変換行列配列を取得する
		auto preMatrices = m_motionArray.getMatchHandlePtr(preHandle)->calculateBoneTransformMatrices(preFrame);

		// 座標変換配列の補完結果の値
		std::vector<MotionBoneParam> result;
		result.reserve(curMatrices.size());

		// モーションの座標変換行列配列を巡回する
		for (size_t i = 0; i < curMatrices.size(); i++)
		{
			MotionBoneParam boneParam{};

			// 対象のボーンの名称を設定
			boneParam.boneName = curMatrices.at(i).boneName;

			// 前フレームと今フレームの座標変換行列を線形補完する
			boneParam.transform = tktkMath::Matrix4::lerp(
				preMatrices.at(i).transform,
				curMatrices.at(i).transform,
				amount
			);

			// 計算した座標変換行列を配列に追加
			result.push_back(boneParam);
		}

		// 計算結果を返す
		return result;
	}
}