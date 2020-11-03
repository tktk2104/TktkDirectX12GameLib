#include "TktkDX12BaseComponents/2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"

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

	ColliderWireFrameDrawer2DMaker& ColliderWireFrameDrawer2DMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = ColliderWireFrameDrawer2DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<ColliderWireFrameDrawer2D> ColliderWireFrameDrawer2DMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<ColliderWireFrameDrawer2D>(
				m_drawPriority,
				m_lineColor
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<ColliderWireFrameDrawer2D>(
			m_drawPriority,
			m_lineColor
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
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