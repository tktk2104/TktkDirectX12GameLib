#ifndef TKTK_DX12_GAME_H_
#define TKTK_DX12_GAME_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "_MainManager/DX12GameManager.h"

namespace tktk
{
	// ゲームの各種処理を呼ぶ
	// ※細かい処理を呼びたい場合は「DX12GameManager」を使ってください
	class DX12Game
	{
	//************************************************************
	/* ウィンドウの処理 */
	public:

		// ウィンドウサイズを取得する
		static const tktkMath::Vector2& getWindowSize();

	//************************************************************
	/* シーンの処理 */
	public:

		// シーンを有効にする
		template <class SceneType>
		static void enableScene(SceneType id);

		// シーンを無効にする
		template <class SceneType>
		static void disableScene(SceneType id);

	//************************************************************
	/* ゲームオブジェクトの処理 */
	public:

		// 全てのGameObjectにメッセージを送信する
		template <class MessageIdType>
		static void sendMessageAll(MessageIdType messageId, const MessageAttachment& value = {});

		// ゲームオブジェクトを作成し、そのポインタを返す
		static GameObjectPtr createGameObject();

		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		template <class GameObjectTagType>
		static GameObjectPtr findGameObjectWithTag(GameObjectTagType tag);

		// 引数のタグを持ったゲームオブジェクトを全て取得する
		template <class GameObjectTagType>
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagType tag);

	//************************************************************
	/* マウス入力関係の処理 */
	public:

		// 指定のボタンが押されているか
		static bool isPush(MouseButtonType buttonType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseButtonType buttonType);

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* キーボード入力関係の処理 */
	public:

		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);

	//************************************************************
	/* ゲームパッド入力関係の処理 */
	public:

		// 左スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getLstick();

		// 右スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getRstick();

		// 指定のボタンが押されているかを判定
		static bool isPush(GamePadBtnType buttonType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(GamePadBtnType buttonType);

	//************************************************************
	/* タイム関係の処理 */
	public:

		// 経過時間を初期化する
		static void resetElapsedTime();

		// 前フレームとの時間の差を求める
		static float deltaTime();

		// 前フレームとの時間の差を求める（TimeScaleを無視）
		static float noScaleDeltaTime();

		// プログラムが起動してからの時間（秒）を返す
		static float getCurTimeSec();

		// 最大のdeltaTimeの値を設定（正の数）
		static void setMaximumDeltaTime(float maximumDeltaTime);

		// 時間の経過速度割合を取得する
		static float getTimeScale();

		// 時間の経過速度割合を設定する（0.0～float_max）
		static void setTimeScale(float timeScaleRate);

		// 基準となるFPSを設定する
		static void setBaseFps(unsigned int baseFps = 60U);

		// 基準となるFPSを取得する
		static unsigned int getBaseFps();

		// 瞬間的なFPSを取得する
		static float fps();

	//************************************************************
	/* 非テンプレート関数 */
	private:

		static void enableSceneImpl(unsigned int id);
		static void disableSceneImpl(unsigned int id);
		static void sendMessageAllImpl(unsigned int messageId, const MessageAttachment& value);
		static GameObjectPtr findGameObjectWithTagImpl(int tag);
		static std::forward_list<GameObjectPtr> findGameObjectsWithTagImpl(int tag);
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// シーンを有効にする
	template<class SceneType>
	inline void DX12Game::enableScene(SceneType id)
	{
		enableSceneImpl(static_cast<unsigned int>(id));
	}

	// シーンを無効にする
	template<class SceneType>
	inline void DX12Game::disableScene(SceneType id)
	{
		disableSceneImpl(static_cast<unsigned int>(id));
	}

	// 全てのGameObjectにメッセージを送信する
	template<class MessageIdType>
	inline void DX12Game::sendMessageAll(MessageIdType messageId, const MessageAttachment& value)
	{
		sendMessageAllImpl(static_cast<unsigned int>(messageId), value);
	}

	// 引数のタグを持ったゲームオブジェクトを取得する
	// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
	template<class GameObjectTagType>
	inline GameObjectPtr DX12Game::findGameObjectWithTag(GameObjectTagType tag)
	{
		return findGameObjectWithTagImpl(static_cast<int>(tag));
	}

	// 引数のタグを持ったゲームオブジェクトを全て取得する
	template<class GameObjectTagType>
	inline std::forward_list<GameObjectPtr> DX12Game::findGameObjectsWithTag(GameObjectTagType tag)
	{
		return findGameObjectsWithTagImpl(static_cast<int>(tag));
	}
}
#endif // !TKTK_DX12_GAME_H_