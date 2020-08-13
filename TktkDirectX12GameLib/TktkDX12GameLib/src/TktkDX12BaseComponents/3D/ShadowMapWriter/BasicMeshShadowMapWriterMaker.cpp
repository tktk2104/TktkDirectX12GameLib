#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BasicMeshShadowMapWriterMaker.h"

namespace tktk
{
	BasicMeshShadowMapWriterMaker BasicMeshShadowMapWriterMaker::m_self;

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BasicMeshShadowMapWriterMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BasicMeshShadowMapWriter> BasicMeshShadowMapWriterMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<BasicMeshShadowMapWriter>(
			m_drawPriority,
			m_meshId,
			m_skeletonId,
			m_cameraId
			);
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::meshIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_meshId = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::skeletonIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonId = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::cameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraId = value;
		return *this;
	}
}