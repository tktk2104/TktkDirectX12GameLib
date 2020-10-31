#ifndef TKTK_DX12_GAME_H_
#define TKTK_DX12_GAME_H_

#include <forward_list>
#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "EventMessage/MessageAttachment.h"
#include "GameObject/GameObjectPtr.h"
#include "_MainManager/DX12GameManagerFuncArgsIncluder.h"

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
		// ※内部で対応するリソースハンドルに変換される
		template <class SceneType>
		static void enableScene(SceneType id);

		// シーンを無効にする
		// ※内部で対応するリソースハンドルに変換される
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
		// ※該当オブジェクトが無かった場合、空のGameObjectPtrを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		template <class GameObjectTagType>
		static GameObjectPtr findGameObjectWithTag(GameObjectTagType tag);

		// 引数のタグを持ったゲームオブジェクトを全て取得する
		template <class GameObjectTagType>
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagType tag);

		// 引数のタグを持ったゲームオブジェクトを全て削除する
		template<class GameObjectTagType>
		void destroyGameObjectsWithTag(GameObjectTagType tag) { destroyGameObjectsWithTagImpl(static_cast<int>(tag)); }

	//************************************************************
	/* 入力関係の処理 */
	public:

		// 特定の入力が押されているかを始める
		// 「対応する入力：MouseButtonType, KeybordKeyType, GamePadBtnType」
		// 上記以外の引数の型の場合、InputManagerを使った入力検知になる
		template <class T>
		static bool isPush(T type);

		// 特定の入力が押され始めたかを始める
		// 「対応する入力：MouseButtonType, KeybordKeyType, GamePadBtnType」
		// 上記以外の引数の型の場合、InputManagerを使った入力検知になる
		template <class T>
		static bool isTrigger(T type);

		// 移動方向を取得
		static const tktkMath::Vector2& moveVec();

		// 視点移動方向を取得
		static const tktkMath::Vector2& lookVec();

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

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

		// 時間の経過速度割合を設定する（0.0〜float_max）
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

		static void enableSceneImpl(int id);
		static void disableSceneImpl(int id);
		static void sendMessageAllImpl(unsigned int messageId, const MessageAttachment& value);
		static GameObjectPtr findGameObjectWithTagImpl(int tag);
		static std::forward_list<GameObjectPtr> findGameObjectsWithTagImpl(int tag);
		static void destroyGameObjectsWithTagImpl(int tag);

		static bool isPushImpl(int commandId);
		static bool isPushImpl(MouseButtonType buttonType);
		static bool isPushImpl(KeybordKeyType keyType);
		static bool isPushImpl(GamePadBtnType btnType);

		static bool isTriggerImpl(int commandId);
		static bool isTriggerImpl(MouseButtonType buttonType);
		static bool isTriggerImpl(KeybordKeyType keyType);
		static bool isTriggerImpl(GamePadBtnType btnType);
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// シーンを有効にする
	// ※内部で対応するリソースハンドルに変換される
	template<class SceneType>
	inline void DX12Game::enableScene(SceneType id)
	{
		enableSceneImpl(static_cast<int>(id));
	}

	// シーンを無効にする
	// ※内部で対応するリソースハンドルに変換される
	template<class SceneType>
	inline void DX12Game::disableScene(SceneType id)
	{
		disableSceneImpl(static_cast<int>(id));
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

	// IDに対応した入力が押されているかを判定
	template<class T>
	inline bool DX12Game::isPush(T type)
	{
		return isPushImpl(static_cast<int>(type));
	}

	// 指定のマウスボタンが押されているか
	template<>
	inline bool DX12Game::isPush(MouseButtonType type)
	{
		return isPushImpl(type);
	}

	// 指定のキーが押されているかを判定
	template<>
	inline bool DX12Game::isPush(KeybordKeyType type)
	{
		return isPushImpl(type);
	}

	// 指定のパッドボタンが押されているかを判定
	template<>
	inline bool DX12Game::isPush(GamePadBtnType type)
	{
		return isPushImpl(type);
	}

	template<class T>
	inline bool DX12Game::isTrigger(T type)
	{
		return isTriggerImpl(static_cast<int>(type));
	}

	// 指定のマウスボタンが押され始めたかを判定
	template<>
	inline bool DX12Game::isTrigger(MouseButtonType type)
	{
		return isTriggerImpl(type);
	}

	// 指定のキーが押され始めたかを判定
	template<>
	inline bool DX12Game::isTrigger(KeybordKeyType type)
	{
		return isTriggerImpl(type);
	}

	// 指定のパッドボタンが押され始めたかを判定
	template<>
	inline bool DX12Game::isTrigger(GamePadBtnType type)
	{
		return isTriggerImpl(type);
	}
}
#endif // !TKTK_DX12_GAME_H_