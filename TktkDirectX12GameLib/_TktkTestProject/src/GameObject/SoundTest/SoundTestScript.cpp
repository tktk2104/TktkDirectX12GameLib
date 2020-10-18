#include "SoundTestScript.h"

#include <TktkDX12Game/TktkDX12Game.h>

void SoundTestScript::update()
{
	if (tktk::DX12Game::isTrigger(tktk::KeybordKeyType::key_P))
	{
		getComponent<tktk::SoundPlayer>()->playSound();
	}
}
