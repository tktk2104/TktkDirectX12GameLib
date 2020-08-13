#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteDrawerMaker.h"

namespace tktk
{
	SpriteDrawerMaker SpriteDrawerMaker::m_self;

	SpriteDrawerMaker& SpriteDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SpriteDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープIDのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SpriteDrawer> SpriteDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<SpriteDrawer>(
			m_drawPriority,
			m_spriteMaterialId,
			m_useRtvDescriptorHeapId
			);
	}

	SpriteDrawerMaker& SpriteDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	SpriteDrawerMaker& SpriteDrawerMaker::spriteMaterialIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_spriteMaterialId = value;
		return *this;
	}
}