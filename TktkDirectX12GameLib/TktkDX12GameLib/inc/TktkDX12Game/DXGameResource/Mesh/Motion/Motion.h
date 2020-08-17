#ifndef MOTION_H_
#define MOTION_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "MotionData.h"

namespace tktk
{
	// 「MotionData」を管理するクラス
	class Motion
	{
	public:

		Motion(unsigned int motionNum);

	public:

		// vmdファイルを読み込んで「MotionData」のインスタンスを作る
		void load(unsigned int id, const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		unsigned int getEndFrameNo(unsigned int id) const;

		// ２つのフレームのボーン毎の行列と補完割合を使用し、線形補完したボーン毎の行列を計算する（キーが無い時は前後のキーから計算する）
		// ※補完割合の値は「0.0でpreFrame100%」、「1.0でcurFrame100%」となる
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(unsigned int curId, unsigned int preId, unsigned int curFrame, unsigned int preFrame, float amount) const;

	private:

		tktkContainer::HeapArray<MotionData> m_motionArray;
	};
}
#endif // !MOTION_H_