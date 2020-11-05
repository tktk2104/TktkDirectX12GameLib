#ifndef SOUND_PLAYER_H_
#define SOUND_PLAYER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	// サウンド再生コンポーネント
	class SoundPlayer
		: public ComponentBase
	{
	public:

		SoundPlayer(size_t soundHandle, bool isLoop, bool startToPlay);

	public:

		void playSound();

		void stopSound();

		void pauseSound();

		// 新たなサウンドハンドルを設定し、再生する
		void changeSoundHandle(size_t soundHandle);

		// 新たなサウンドIDを設定し、再生する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		void changeSoundId(ResourceIdCarrier soundId);

	public:

		void start();

		void onEnable();

		void onDisable();

		void onDestroy();

	private:

		size_t	m_soundHandle;
		bool	m_isLoop;
		bool	m_startToPlay;
	};
}
#endif // !SOUND_PLAYER_H_