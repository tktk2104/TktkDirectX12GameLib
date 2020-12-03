#ifndef EVENT_MESSAGE_TYPE_H_
#define EVENT_MESSAGE_TYPE_H_

// 送信するメッセージの種類
enum class EventMessageType
{
	Damage,			// ダメージを受けた
	Dead,			// 死んだ

	LookToEnemy,	// 敵の方を強制的に向かせる
};
#endif // !EVENT_MESSAGE_TYPE_H_