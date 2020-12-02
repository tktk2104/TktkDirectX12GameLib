#ifndef MOTION_H_
#define MOTION_H_

/* std::vector */
#include <vector>

/* std::string */
#include <string>

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class MotionData;
	struct MotionBoneParam;

	// 「MotionData」を管理するクラス
	class MotionManager
	{
	public:

		explicit MotionManager(const tktkContainer::ResourceContainerInitParam& initParam);
		~MotionManager();

	public:

		// vmdファイルを読み込んで「MotionData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t load(const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		size_t getEndFrameNo(size_t handle) const;

		// ２つのフレームのボーン毎の行列と補完割合を使用し、線形補完したボーン毎の行列を計算する（キーが無い時は前後のキーから計算する）
		// ※補完割合の値は「0.0でpreFrame100%」、「1.0でcurFrame100%」となる
		std::vector<MotionBoneParam> calculateBoneTransformMatrices(size_t curHandle, size_t preHandle, float curFrame, float preFrame, float amount) const;

	private:

		tktkContainer::ResourceContainer<MotionData> m_motionArray;
	};
}
#endif // !MOTION_H_