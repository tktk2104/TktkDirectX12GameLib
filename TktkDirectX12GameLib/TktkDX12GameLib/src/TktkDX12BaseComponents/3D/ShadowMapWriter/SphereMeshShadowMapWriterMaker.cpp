#include "TktkDX12BaseComponents/3D/ShadowMapWriter/SphereMeshShadowMapWriterMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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
		// コンポーネントを作成する
		return m_user->createComponent<SphereMeshShadowMapWriter>(
			m_drawPriority,
			m_radius,
			m_localPosition,
			m_cameraHandle
			);
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

	SphereMeshShadowMapWriterMaker& SphereMeshShadowMapWriterMaker::cameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}