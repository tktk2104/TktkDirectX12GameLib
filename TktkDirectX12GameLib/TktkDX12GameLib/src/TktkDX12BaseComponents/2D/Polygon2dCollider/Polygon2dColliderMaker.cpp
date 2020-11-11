#include "TktkDX12BaseComponents/2D/Polygon2dCollider/Polygon2dColliderMaker.h"

#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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
		// コンポーネントを作成する
		return m_user->createComponent<Polygon2dCollider>(
			m_collisionGroupType,
			m_vertexs,
			m_isExtrude,
			m_extrudedRate
			);
	}

	Polygon2dColliderMaker& Polygon2dColliderMaker::collisionGroupType(CollisionGroupTypeCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_collisionGroupType = value;
		return *this;
	}

	Polygon2dColliderMaker & Polygon2dColliderMaker::vertexs(const std::vector<tktkMath::Vector2> & value)
	{
		// 値を設定して自身の参照を返す
		m_vertexs = value;
		return *this;
	}

	Polygon2dColliderMaker& Polygon2dColliderMaker::isExtrude(bool value)
	{
		// 値を設定して自身の参照を返す
		m_isExtrude = value;
		return *this;
	}

	Polygon2dColliderMaker& Polygon2dColliderMaker::extrudedRate(float value)
	{
		// 値を設定して自身の参照を返す
		m_extrudedRate = value;
		return *this;
	}
}