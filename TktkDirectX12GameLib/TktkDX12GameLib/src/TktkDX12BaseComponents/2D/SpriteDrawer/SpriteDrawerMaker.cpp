#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SpriteDrawerMaker SpriteDrawerMaker::m_self;

	SpriteDrawerMaker& SpriteDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SpriteDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SpriteDrawer> SpriteDrawerMaker::create()
	{
		const auto& textureSize = DX12GameManager::getSpriteTextureSize(m_spriteMaterialHandle);

		// コンポーネントを作成する
		return m_user->createComponent<SpriteDrawer>(
			m_drawPriority,
			m_spriteMaterialHandle,
			m_localPosition,
			m_localScaleRate,
			m_localRotationDeg,
			m_centerRate,
			m_blendRate,
			tktkMath::Vector2::scale(textureSize, m_leftTopPosRate),
			tktkMath::Vector2::scale(textureSize, m_sizeRate)
			);
	}

	SpriteDrawerMaker& SpriteDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::spriteMaterialHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_spriteMaterialHandle = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::spriteMaterialId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::localPosition(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::localScaleRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_localScaleRate = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::localRotationDeg(float value)
	{
		// 値を設定して自身の参照を返す
		m_localRotationDeg = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_centerRate = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::blendRate(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_blendRate = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::clippingLeftTopPosRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_leftTopPosRate = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::clippingSizeRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_sizeRate = value;
		return *this;
	}
}