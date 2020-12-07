#include "TktkDX12BaseComponents/2D/SpriteAnimator/SpriteAnimatorMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SpriteAnimatorMaker SpriteAnimatorMaker::m_self;

	SpriteAnimatorMaker& SpriteAnimatorMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SpriteAnimatorMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SpriteAnimator> SpriteAnimatorMaker::create()
	{
		return m_user->createComponent<SpriteAnimator>(
			m_initFrame,
			m_isLoop,
			m_animSpeedRate,
			m_animFramePerSec,
			m_totalAnimFrameSize
			);
	}

	SpriteAnimatorMaker& SpriteAnimatorMaker::isLoop(bool value)
	{
		m_isLoop = value;
		return *this;
	}

	SpriteAnimatorMaker& SpriteAnimatorMaker::initFrame(float value)
	{
		m_initFrame = value;
		return *this;
	}

	SpriteAnimatorMaker& SpriteAnimatorMaker::animSpeedRate(float value)
	{
		m_animSpeedRate = value;
		return *this;
	}

	SpriteAnimatorMaker& SpriteAnimatorMaker::animFramePerSec(float value)
	{
		m_animFramePerSec = value;
		return *this;
	}

	SpriteAnimatorMaker& SpriteAnimatorMaker::totalAnimFrameSize(unsigned int value)
	{
		m_totalAnimFrameSize = value;
		return *this;
	}
}