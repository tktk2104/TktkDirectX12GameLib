#ifndef SHT_2D_GAME_CLEAR_MESSAGE_SENDER_H_
#define SHT_2D_GAME_CLEAR_MESSAGE_SENDER_H_

#include <TktkDX12GameLib.h>

class Sht2D_GameClearMessageSender
	: public tktk::ComponentBase
{
public:

	Sht2D_GameClearMessageSender() = default;

public:

	void onEnable();
};
#endif // !SHT_2D_GAME_CLEAR_MESSAGE_SENDER_H_