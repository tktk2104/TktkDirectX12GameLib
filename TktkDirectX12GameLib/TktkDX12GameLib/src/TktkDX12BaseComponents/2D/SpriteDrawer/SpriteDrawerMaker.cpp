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

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SpriteDrawer> SpriteDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<SpriteDrawer>(
			m_drawPriority,
			m_spriteMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_centerRate
			);
	}

	SpriteDrawerMaker& SpriteDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
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

	SpriteDrawerMaker& SpriteDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_centerRate = value;
		return *this;
	}
}