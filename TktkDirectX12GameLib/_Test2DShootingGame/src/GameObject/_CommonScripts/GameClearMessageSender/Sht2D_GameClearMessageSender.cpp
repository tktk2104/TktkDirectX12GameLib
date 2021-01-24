#include "Sht2D_GameClearMessageSender.h"

#include "../../../Enums/Enums.h"

void Sht2D_GameClearMessageSender::onEnable()
{
	tktk::DX12Game::sendMessageAll(EventMessageType::GameClear);
}