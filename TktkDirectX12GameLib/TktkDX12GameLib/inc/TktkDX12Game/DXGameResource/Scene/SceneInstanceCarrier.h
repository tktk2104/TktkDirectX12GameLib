#ifndef SCENE_INSTANCE_CARRIER_H_
#define SCENE_INSTANCE_CARRIER_H_

#include "SceneVTable.h"

namespace tktk
{
	// シーンのインスタンスを保持するクラス
	class SceneInstanceCarrier
	{
	public:

		SceneInstanceCarrier(const std::shared_ptr<SceneBase>& scenePtr, SceneVTable* vtablePtr);
		~SceneInstanceCarrier();

		// ムーブコンストラクタ
		SceneInstanceCarrier(SceneInstanceCarrier&& other) noexcept;

	public:

		// シーンを有効にする
		void enable();

		// シーンを無効にする
		void disable();

		// シーンが有効、無効状態を切り替える
		void changeActive();

		// シーンの更新処理
		void update();

	private:

		bool						m_isActive					{ false };
		bool						m_nextFrameIsActive			{ false };
		bool						m_runAfterChangeActiveFunc	{ false };
		std::shared_ptr<SceneBase>	m_scenePtr					{ nullptr };
		SceneVTable*				m_vtablePtr					{ nullptr };
	};
}
#endif // !SCENE_INSTANCE_CARRIER_H_