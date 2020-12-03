#ifndef SOUND_PLAY_TIMER_MAKER_H_
#define SOUND_PLAY_TIMER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SoundPlayTimer.h"

namespace tktk
{
	class SoundPlayTimerMaker
	{
	private: /* プライベートコンストラクタ達 */

		SoundPlayTimerMaker() = default;
		SoundPlayTimerMaker(const SoundPlayTimerMaker& other) = default;
		SoundPlayTimerMaker& operator = (const SoundPlayTimerMaker& other) = default;

	public:

		// インスタンス作成開始
		static SoundPlayTimerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		ComponentPtr<SoundPlayTimer> create();

	public:

		// サウンドハンドルの設定
		SoundPlayTimerMaker& soundHandle(size_t value);

		// サウンドIDの設定（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		SoundPlayTimerMaker& soundId(ResourceIdCarrier value);

		// 最初の再生を行うまでの時間
		SoundPlayTimerMaker& firstPlayStartTimeSec(float value);

		// 何秒間の間隔を空けて再生するか？
		SoundPlayTimerMaker& playIntervalSec(float value);

		// 一度のタイマーで何回再生するかを設定する
		SoundPlayTimerMaker& playCount(int value);

		// 生成直後にサウンドを再生するかを設定する
		SoundPlayTimerMaker& startToPlay(bool value);

	private:

		// 自身のポインタ
		static SoundPlayTimerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr		m_user{ };
		size_t				m_soundHandle{ 0U };
		float				m_firstPlayStartTimeSec{ 0.0f };
		float				m_playIntervalSec{ 3.0f };
		int					m_playCount{ 10 };
		bool				m_startToPlay{ false };
	};
}
#endif // !SOUND_PLAY_TIMER_MAKER_H_