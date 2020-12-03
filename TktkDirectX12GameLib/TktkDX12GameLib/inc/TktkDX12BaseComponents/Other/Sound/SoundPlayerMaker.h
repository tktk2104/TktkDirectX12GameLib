#ifndef SOUND_PLAYER_MAKER_H_
#define SOUND_PLAYER_MAKER_H_

#include "SoundPlayer.h"

namespace tktk
{
	class SoundPlayerMaker
	{
	private: /* プライベートコンストラクタ達 */

		SoundPlayerMaker() = default;
		SoundPlayerMaker(const SoundPlayerMaker& other) = default;
		SoundPlayerMaker& operator = (const SoundPlayerMaker& other) = default;

	public:

		// インスタンス作成開始
		static SoundPlayerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<SoundPlayer> create();

	public:

		// サウンドハンドルの設定
		SoundPlayerMaker& soundHandle(size_t soundHandle);

		// サウンドIDの設定（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		SoundPlayerMaker& soundId(ResourceIdCarrier value);

		// サウンドのループフラグを設定する
		SoundPlayerMaker& isLoop(bool value);

		// 生成直後にサウンドを再生するかを設定する
		SoundPlayerMaker& startToPlay(bool value);

	private:

		// 自身のポインタ
		static SoundPlayerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user			{ };
		size_t				m_soundHandle	{ 0U };
		bool				m_isLoop		{ false };
		bool				m_startToPlay	{ false };
	};
}
#endif // !SOUND_PLAYER_MAKER_H_