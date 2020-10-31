#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dColliderMaker.h"

namespace tktk
{
	Polygon2dColliderMaker Polygon2dColliderMaker::m_self;

	Polygon2dColliderMaker & Polygon2dColliderMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = Polygon2dColliderMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<Polygon2dCollider> Polygon2dColliderMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<Polygon2dCollider>(
				m_collisionGroupType,
				m_vertexs,
				m_extrudedRate
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<Polygon2dCollider>(
			m_collisionGroupType,
			m_vertexs,
			m_extrudedRate
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	Polygon2dColliderMaker & Polygon2dColliderMaker::vertexs(const std::vector<tktkMath::Vector2> & value)
	{
		// 値を設定して自身の参照を返す
		m_vertexs = value;
		return *this;
	}

	Polygon2dColliderMaker& Polygon2dColliderMaker::extrudedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_extrudedRate = value;
		return *this;
	}

	Polygon2dColliderMaker& Polygon2dColliderMaker::collisionGroupTypeImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}
}