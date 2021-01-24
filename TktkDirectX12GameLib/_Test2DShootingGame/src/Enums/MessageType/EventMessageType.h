#ifndef EVENT_MESSAGE_TYPE_H_
#define EVENT_MESSAGE_TYPE_H_

// 送信するメッセージの種類
enum class EventMessageType
{
	Damage,			// ダメージを受けた
	
	GameClear,		// ゲームをクリアした
};
#endif // !EVENT_MESSAGE_TYPE_H_