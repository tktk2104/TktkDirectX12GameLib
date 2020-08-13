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
	public: /* ウィンドウの処理 */

		// ウィンドウサイズを取得する
		static const tktkMath::Vector2& getWindowSize();

	public: /* シーンの処理 */

		// シーンを有効にする
		static void enableScene(unsigned int id);

		// シーンを無効にする
		static void disableScene(unsigned int id);

	public: /* ゲームオブジェクトの処理 */

		// 全てのGameObjectにメッセージを送信する
		static void SendMessageAll(unsigned int messageId, const MessageAttachment& value = {});

		// ゲームオブジェクトを作成し、そのポインタを返す
		static GameObjectPtr createGameObject();

		// 引数のタグを持ったゲームオブジェクトを取得する
		// ※複数該当オブジェクトがあった場合、最初に見つけた１つを取得する
		template <class GameObjectTagType>
		static GameObjectPtr findGameObjectWithTag(GameObjectTagType tag);

		// 引数のタグを持ったゲームオブジェクトを全て取得する
		template <class GameObjectTagType>
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagType tag);

	public: /* マウス入力関係の処理 */

		// 指定のボタンが押されているか
		static bool isPush(MouseButtonType buttonType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(MouseButtonType buttonType);

		// マウスカーソルの座標を取得する
		static tktkMath::Vector2 mousePos();

	public: /* キーボード入力関係の処理 */

		// 指定のキーが押されているかを判定
		static bool isPush(KeybordKeyType keyType);

		// 指定のキーが押され始めたかを判定
		static bool isTrigger(KeybordKeyType keyType);

	public: /* ゲームパッド入力関係の処理 */

		// 左スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getLstick();

		// 右スティックの傾きを取得（-1.0～1.0の間）
		static tktkMath::Vector2 getRstick();

		// 指定のボタンが押されているかを判定
		static bool isPush(GamePadBtnType btnType);

		// 指定のボタンが押され始めたかを判定
		static bool isTrigger(GamePadBtnType btnType);

	public: /* タイム関係の処理 */

		// 経過時間を初期化する
		static void reset();

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

	private:

		// 非テンプレート関数
		static GameObjectPtr findGameObjectWithTagImpl(int tag);
		static std::forward_list<GameObjectPtr> findGameObjectsWithTagImpl(int tag);
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


	template<class GameObjectTagType>
	inline GameObjectPtr DX12Game::findGameObjectWithTag(GameObjectTagType tag)
	{
		return GameObjectPtr();
	}

	template<class GameObjectTagType>
	inline std::forward_list<GameObjectPtr> DX12Game::findGameObjectsWithTag(GameObjectTagType tag)
	{
		return std::forward_list<GameObjectPtr>();
	}

}
#endif // !TKTK_DX12_GAME_H_