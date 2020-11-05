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

		// 使用するカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// 自身の参照を返す
		return m_self;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BasicMeshShadowMapWriterMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 使用するカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BasicMeshShadowMapWriter> BasicMeshShadowMapWriterMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<BasicMeshShadowMapWriter>(
				m_drawPriority,
				m_baseScale,
				m_baseRotation,
				m_meshHandle,
				m_skeletonHandle,
				m_cameraHandle
				);
		}
		
		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<BasicMeshShadowMapWriter>(
			m_drawPriority,
			m_baseScale,
			m_baseRotation,
			m_meshHandle,
			m_skeletonHandle,
			m_cameraHandle
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::baseScale(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_baseScale = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::baseRotation(const tktkMath::Quaternion& value)
	{
		// 値を設定して自身の参照を返す
		m_baseRotation = value;
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::meshId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_meshHandle = DX12GameManager::getBasicMeshHandle(value);
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::skeletonId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_skeletonHandle = DX12GameManager::getSkeletonHandle(value);
		return *this;
	}

	BasicMeshShadowMapWriterMaker& BasicMeshShadowMapWriterMaker::cameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}