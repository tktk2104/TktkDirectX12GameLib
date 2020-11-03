#ifndef SOUND_PLAYER_MAKER_H_
#define SOUND_PLAYER_MAKER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
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

		// ステートを指定し、作成を開始する
		static SoundPlayerMaker& makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<SoundPlayer> create();

	public:

		// サウンドハンドルの設定
		SoundPlayerMaker& soundHandle(unsigned int soundHandle);

		// サウンドIDの設定（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		template<class IdType, is_idType<IdType> = nullptr>
		SoundPlayerMaker& soundId(IdType value) { return soundIdImpl(static_cast<int>(value)); }

		// サウンドのループフラグを設定する
		SoundPlayerMaker& isLoop(bool value);

		// 生成直後にサウンドを再生するかを設定する
		SoundPlayerMaker& startToPlay(bool value);

	private: /* 各種id指定系の関数の実装 */

		SoundPlayerMaker& soundIdImpl(int value);

	private:

		// 自身のポインタ
		static SoundPlayerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user			{ };
		StateTypeHierarchy		m_targetState	{ };
		unsigned int		m_soundHandle	{ 0U };
		bool				m_isLoop		{ false };
		bool				m_startToPlay	{ false };

	public: /* 不正な型の引数が渡されそうになった時にコンパイルエラーにする為の仕組み */

		template<class IdType, is_not_idType<IdType> = nullptr>
		SoundPlayerMaker& soundId(IdType value) { static_assert(false, "SoundId Fraud Type"); }
	};
}
#endif // !SOUND_PLAYER_MAKER_H_