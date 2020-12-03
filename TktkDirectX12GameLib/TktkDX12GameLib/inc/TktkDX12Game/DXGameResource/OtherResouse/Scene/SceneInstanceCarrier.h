#ifndef SCENE_INSTANCE_CARRIER_H_
#define SCENE_INSTANCE_CARRIER_H_

/* std::shared_ptr, std::unique_ptr  */
#include <memory>

/* funcUseType */
#include "../../GameObjectResouse/GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	struct SceneInitParam;
	struct SceneVTable;
	class SceneBase;

	// シーンのインスタンスを保持するクラス
	class SceneInstanceCarrier
	{
	public:

		explicit SceneInstanceCarrier(const SceneInitParam& initParam);
		~SceneInstanceCarrier();

		// ムーブコンストラクタ
		SceneInstanceCarrier(SceneInstanceCarrier&& other) noexcept;

	public:

		// シーンの終了時に削除するゲームオブジェクトタグを設定する
		void setSceneEndDestroyGameObjectTag(GameObjectTagCarrier tag);

		// シーンを有効にする
		void enable();

		// シーンを無効にする
		void disable();

		// シーンが有効、無効状態を切り替える
		void changeActive();

		// シーンの更新処理
		void update();

	private:

		bool									m_isActive					{ false };
		bool									m_nextFrameIsActive			{ false };
		bool									m_runAfterChangeActiveFunc	{ false };
		std::unique_ptr<GameObjectTagCarrier>	m_destroyGameObjectTag		{ nullptr };
		std::shared_ptr<SceneBase>				m_scenePtr					{ nullptr };
		SceneVTable*							m_vtablePtr					{ nullptr };
	};
}
#endif // !SCENE_INSTANCE_CARRIER_H_