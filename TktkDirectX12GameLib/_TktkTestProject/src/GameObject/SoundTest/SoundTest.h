#ifndef SOUND_TEST_H_
#define SOUND_TEST_H_

#include <TktkDX12Game/TktkDX12Game.h>
#include <TktkDX12BaseComponents/Components.h>

#include "../../Enum/_ResourceIds/ResourceIds.h"
#include "SoundTestScript.h"

struct SoundTest
{
	static tktk::GameObjectPtr create()
	{
		auto gameObject = tktk::DX12GameManager::createGameObject();

		tktk::SoundPlayerMaker::makeStart(gameObject)
			.soundId(SoundId::TestSe)
			.startToPlay(false)
			.isLoop(false)
			.create();

		gameObject->createComponent<SoundTestScript>();

		return gameObject;
	}
};
#endif // !SOUND_TEST_H_
