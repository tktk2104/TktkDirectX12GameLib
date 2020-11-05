#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawerMaker.h"

namespace tktk
{
	BillboardDrawerMaker BillboardDrawerMaker::m_self;

	BillboardDrawerMaker& BillboardDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BillboardDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BillboardDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BillboardDrawer> BillboardDrawerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			return m_user->createComponent<BillboardDrawer>(
				m_drawPriority,
				m_billboardMaterialHandle,
				m_useRtvDescriptorHeapHandle,
				m_cameraHandle,
				m_centerRate,
				m_blendRate
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<BillboardDrawer>(
			m_drawPriority,
			m_billboardMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_cameraHandle,
			m_centerRate,
			m_blendRate
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::billboardMaterialHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_billboardMaterialHandle = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::cameraHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::cameraId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::billboardMaterialId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(value);
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_centerRate = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::blendRate(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_blendRate = value;
		return *this;
	}
}