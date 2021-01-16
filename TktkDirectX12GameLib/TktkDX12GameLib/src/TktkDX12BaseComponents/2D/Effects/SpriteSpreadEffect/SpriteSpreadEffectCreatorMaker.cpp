#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/SpriteSpreadEffectCreatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SpriteSpreadEffectCreatorMaker SpriteSpreadEffectCreatorMaker::m_self;

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SpriteSpreadEffectCreatorMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SpriteSpreadEffectCreator> SpriteSpreadEffectCreatorMaker::create()
	{
		return m_user->createComponent<SpriteSpreadEffectCreator>(m_param);
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateLocalPos(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateLocalPos = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateLocalPosRandomRange(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateLocalPosRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::minGenerateAngleDeg(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.minGenerateAngleDeg = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::maxGenerateAngleDeg(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.maxGenerateAngleDeg = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::firstGenerateTimeSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.firstGenerateTimeSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateIntervalTimeSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateIntervalTimeSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateIntervalTimeRandomRange(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateIntervalTimeRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateNumPerOnce(int value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateNumPerOnce = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateNumPerOnceRandomRange(int value)
	{
		// 値を設定して自身の参照を返す
		m_param.generateNumPerOnceRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::totalGenerateNum(int value)
	{
		// 値を設定して自身の参照を返す
		m_param.totalGenerateNum = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::changeAvtiveToReset(bool value)
	{
		// 値を設定して自身の参照を返す
		m_param.changeAvtiveToReset = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteMaterialHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_param.useSpriteHandle = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteMaterialId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_param.useSpriteHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteScale(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.spriteScale = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteScaleRandomRange(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_param.spriteScaleRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteBlendRate(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_param.spriteBlendRate = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::setChild(bool value)
	{
		// 値を設定して自身の参照を返す
		m_param.setChild = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::lifeTimeSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.lifeTimeSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::lifeTimeSecRandomRange(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.lifeTimeSecRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::moveSpeedPerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.moveSpeedPerSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::moveSpeedPerSecRandomRange(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.moveSpeedPerSecRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::useAnimation(bool value)
	{
		// 値を設定して自身の参照を返す
		m_param.useAnimation = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::isLoop(bool value)
	{
		// 値を設定して自身の参照を返す
		m_param.isLoop = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::initFrame(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.initFrame = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::animSpeedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.animSpeedRate = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::animFramePerSec(float value)
	{
		// 値を設定して自身の参照を返す
		m_param.animFramePerSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::totalAnimFrameSize(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_param.totalAnimFrameSize = value;
		return *this;
	}
}