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
		// 今のフレームで使用していたモーションの座標変換行列配列を取得する
		auto curMatrices = m_motionArray.at(curId)->calculateBoneTransformMatrices(curFrame);

		// 前フレームと変化が全く無ければ取得した今フレーム情報をそのまま返す
		if (preId == curId && preFrame == curFrame) return curMatrices;

		// モーションの補完割合が１以上だったら今フレーム情報をそのまま返す
		if (amount >= 1.0f) return curMatrices;

		// 前のフレームで使用していたモーションの座標変換行列配列を取得する
		auto preMatrices = m_motionArray.at(preId)->calculateBoneTransformMatrices(preFrame);

		// 座標変換配列の補完結果の値
		std::vector<MotionBoneParam> result;
		result.reserve(curMatrices.size());

		// モーションの座標変換行列配列を巡回する
		for (unsigned int i = 0; i < curMatrices.size(); i++)
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