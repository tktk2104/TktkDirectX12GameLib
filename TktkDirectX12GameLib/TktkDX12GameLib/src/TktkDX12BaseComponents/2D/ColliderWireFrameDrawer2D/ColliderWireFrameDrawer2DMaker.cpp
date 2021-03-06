#include "TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	ColliderWireFrameDrawer2DMaker ColliderWireFrameDrawer2DMaker::m_self;

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = ColliderWireFrameDrawer2DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<ColliderWireFrameDrawer2D> ColliderWireFrameDrawer2DMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<ColliderWireFrameDrawer2D>(
			m_drawPriority,
			m_lineColor
			);
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	ColliderWireFrameDrawer2DMaker & ColliderWireFrameDrawer2DMaker::lineColor(const tktkMath::Color & value)
	{
		// 値を設定して自身の参照を返す
		m_lineColor = value;
		return *this;
	}
}