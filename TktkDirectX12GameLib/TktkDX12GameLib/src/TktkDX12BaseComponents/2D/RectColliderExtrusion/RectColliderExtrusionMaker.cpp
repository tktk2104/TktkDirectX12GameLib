#include "TktkDX12BaseComponents/2D/RectColliderExtrusion/RectColliderExtrusionMaker.h"

namespace tktk
{
	RectColliderExtrusionMaker RectColliderExtrusionMaker::m_self;

	RectColliderExtrusionMaker & RectColliderExtrusionMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = RectColliderExtrusionMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<RectColliderExtrusion> RectColliderExtrusionMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<RectColliderExtrusion>();
	}
}