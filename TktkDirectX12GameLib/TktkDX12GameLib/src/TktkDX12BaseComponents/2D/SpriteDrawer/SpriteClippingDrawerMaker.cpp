#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteClippingDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SpriteClippingDrawerMaker SpriteClippingDrawerMaker::m_self;

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SpriteClippingDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SpriteClippingDrawer> SpriteClippingDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<SpriteClippingDrawer>(
			m_drawPriority,
			m_spriteMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_centerRate,
			m_clippingParam
			);
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::spriteMaterialHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_spriteMaterialHandle = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::spriteMaterialId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_centerRate = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::clippingLeftTopPos(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_clippingParam.leftTopPos = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::clippingSize(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_clippingParam.size = value;
		return *this;
	}
}