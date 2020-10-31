#include "TktkDX12BaseComponents/2D/SpriteDrawer/SpriteClippingDrawerMaker.h"

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
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<SpriteClippingDrawer>(
				m_drawPriority,
				m_spriteMaterialHandle,
				m_useRtvDescriptorHeapHandle,
				m_centerRate,
				m_clippingParam
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<SpriteClippingDrawer>(
			m_drawPriority,
			m_spriteMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_centerRate,
			m_clippingParam
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::spriteMaterialHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_spriteMaterialHandle = value;
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

	SpriteClippingDrawerMaker& SpriteClippingDrawerMaker::spriteMaterialIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_spriteMaterialHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}
}