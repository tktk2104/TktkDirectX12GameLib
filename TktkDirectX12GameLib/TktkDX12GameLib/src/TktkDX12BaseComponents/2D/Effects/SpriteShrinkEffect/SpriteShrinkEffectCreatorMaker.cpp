#include "TktkDX12BaseComponents/2D/Effects/SpriteShrinkEffect/SpriteShrinkEffectCreatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SpriteShrinkEffectCreatorMaker SpriteShrinkEffectCreatorMaker::m_self;

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SpriteShrinkEffectCreatorMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SpriteShrinkEffectCreator> SpriteShrinkEffectCreatorMaker::create()
	{
		return m_user->createComponent<SpriteShrinkEffectCreator>(m_param);
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::shrinkTargetPos(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.shrinkTargetPos = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::shrinkTargetPosRandomRange(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.shrinkTargetPosRandomRange = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::firstGenerateTimeSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.firstGenerateTimeSec = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::generateIntervalTimeSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateIntervalTimeSec = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::generateIntervalTimeRandomRange(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateIntervalTimeRandomRange = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::generateNumPerOnce(int value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateNumPerOnce = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::generateNumPerOnceRandomRange(int value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateNumPerOnceRandomRange = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::totalGenerateNum(int value)
	{
		// 値を設定して自身の参照を返す
		m_param.totalGenerateNum = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::changeAvtiveToReset(bool value)
	{
		// 値を設定して自身の参照を返す
		m_param.changeAvtiveToReset = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::spriteMaterialHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_param.useSpriteHandle = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::spriteMaterialId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_param.useSpriteHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::spriteScale(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.spriteScale = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::spriteScaleRandomRange(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.spriteScaleRandomRange = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::spriteBlendRate(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_param.spriteBlendRate = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::setChild(bool value)
	{
		// 値を設定して自身の参照を返す
		m_param.setChild = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::lifeTimeSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.lifeTimeSec = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::lifeTimeSecRandomRange(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.lifeTimeSecRandomRange = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::moveSpeedPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.moveSpeedPerSec = value;
		return *this;
	}

	SpriteShrinkEffectCreatorMaker& SpriteShrinkEffectCreatorMaker::moveSpeedPerSecRandomRange(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.moveSpeedPerSecRandomRange = value;
		return *this;
	}
}