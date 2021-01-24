#ifndef SHT_2D_GAME_RULE_SCRIPT_H_
#define SHT_2D_GAME_RULE_SCRIPT_H_

#include <TktkDX12GameLib.h>

class Sht2D_GameRuleScript
	: public tktk::ComponentBase
{
public:

	Sht2D_GameRuleScript() = default;

public:

	void start();
	void update();
	void handleMessage(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);

private:

	tktk::GameObjectPtr m_playerObject;
};
#endif // !SHT_2D_GAME_RULE_SCRIPT_H_