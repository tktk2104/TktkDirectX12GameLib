#ifndef OTHER_RESOUSE_H_
#define OTHER_RESOUSE_H_

/* std::unique_ptr */
#include <memory>

/* funcUseType */
#include <string>
#include "../GameObjectResouse/GameObject/GameObjectTagCarrier.h"

namespace tktk
{
	/* class member */
	class SceneManager;
	class SoundManager;

	/* funcUseType */
	struct OtherResouseInitParam;
	struct SceneInitParam;

	// その他のリソースを管理するクラス
	class OtherResouse
	{
	public:

		explicit OtherResouse(const OtherResouseInitParam& initParam);
		~OtherResouse();

	public:

		void update();

	public: /* シーン関係の処理 */

		// シーンを作り、そのリソースのハンドルを返す
		size_t createScene(const SceneInitParam& initParam);

		// シーンの終了時に削除するゲームオブジェクトタグを設定する
		void setSceneEndDestroyGameObjectTag(size_t handle, GameObjectTagCarrier tag);

		// シーンを有効にする
		void enableScene(size_t handle);

		// シーンを無効にする
		void disableScene(size_t handle);

	public: /* サウンド関係の処理 */

		// 読み込んだサウンドをすべて削除する
		void clearSound();

		// 新しいサウンドを読み込み、そのリソースのハンドルを返す
		// ※この関数で読み込めるサウンドの形式は「.wav」のみ
		size_t loadSound(const std::string& fileName);

		// 指定したサウンドを再生する
		void playSound(size_t handle, bool loopPlay);

		// 指定したサウンドを停止する
		void stopSound(size_t handle);

		// 指定したサウンドを一時停止する
		void pauseSound(size_t handle);

		// 大元の音量を変更する（0.0f～1.0f）
		void setMasterVolume(float volume);

	private:

		std::unique_ptr<SceneManager>	m_sceneManager;
		std::unique_ptr<SoundManager>			m_sound;
	};
}
#endif // !OTHER_RESOUSE_H_