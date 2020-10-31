#include "TktkDX12BaseComponents/3D/ShadowMapWriter/SphereMeshShadowMapWriterMaker.h"

namespace tktk
{
	SphereMeshShadowMapWriterMaker SphereMeshShadowMapWriterMaker::m_self;

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = SphereMeshShadowMapWriterMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<SphereMeshShadowMapWriter> SphereMeshShadowMapWriterMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<SphereMeshShadowMapWriter>(
				m_drawPriority,
				m_radius,
				m_localPosition,
				m_cameraHandle
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<SphereMeshShadowMapWriter>(
			m_drawPriority,
			m_radius,
			m_localPosition,
			m_cameraHandle
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::radius(float value)
	{
		// 値を設定して自身の参照を返す
		m_radius = value;
		return *this;
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::localPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_localPosition = value;
		return *this;
	}

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}