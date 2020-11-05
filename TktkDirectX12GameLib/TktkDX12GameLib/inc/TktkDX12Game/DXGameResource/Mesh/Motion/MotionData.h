#ifndef MOTION_DATA_H_
#define MOTION_DATA_H_

#include <string>
#include <vector>
#include <map>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Quaternion.h>
#include <TktkMath/Structs/Matrix4.h>
#include "MotionBoneParam.h"

namespace tktk
{
	// モーションデータを管理するクラス
	class MotionData
	{
	public:

		MotionData(const std::string& motionFileName);

		// ムーブコンストラクタ
		MotionData(MotionData&& other) noexcept;

		~MotionData() = default;

	public:

		// モーションの終了キーの番号を取得する
		size_t getEndFrameNo() const;

		// 指定のフレームのボーン毎の行列を取得する（キーが無い時は前後のキーから計算する）
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(size_t frame) const;

	private:

		// キーフレーム情報
		struct KeyFrame
		{
			size_t					frameNo;
			tktkMath::Vector3		position;
			tktkMath::Vector3		scale;
			tktkMath::Quaternion	rotation;
		};

	private:

		// 現在のフレームに対応したキーフレームを求める
		KeyFrame calculateKeyFrame(const std::vector<KeyFrame>& keyFrames, size_t frame) const;

	private:

		size_t  m_endFrameNo;

		// ボーンごとのキーフレームの配列を管理する連想配列
		std::map<std::string, std::vector<KeyFrame>> m_boneKeyFrames;
	};
}
#endif // !MOTION_DATA_H_