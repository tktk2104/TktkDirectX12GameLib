#include "TktkDX12BaseComponents/3D/ShadowMapWriter/BoxMeshShadowMapWriterMaker.h"

namespace tktk
{
	BoxMeshShadowMapWriterMaker BoxMeshShadowMapWriterMaker::m_self;

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BoxMeshShadowMapWriterMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BoxMeshShadowMapWriter> BoxMeshShadowMapWriterMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<BoxMeshShadowMapWriter>(
			m_drawPriority,
			m_boxSize,
			m_localPosition,
			m_cameraHandle
			);
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::boxSize(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_boxSize = value;
		return *this;
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::localPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	BoxMeshShadowMapWriterMaker& BoxMeshShadowMapWriterMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}