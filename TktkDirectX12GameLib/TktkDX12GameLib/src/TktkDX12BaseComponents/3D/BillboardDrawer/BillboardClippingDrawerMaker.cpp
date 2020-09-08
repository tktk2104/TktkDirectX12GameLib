#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardClippingDrawerMaker.h"

namespace tktk
{
	BillboardClippingDrawerMaker BillboardClippingDrawerMaker::m_self;

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BillboardClippingDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
		m_self.m_cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BillboardClippingDrawer> BillboardClippingDrawerMaker::create()
	{
		return m_user->createComponent<BillboardClippingDrawer>(
			m_drawPriority,
			m_billboardMaterialHandle,
			m_useRtvDescriptorHeapHandle,
			m_cameraHandle,
			m_centerRate,
			m_blendRate,
			m_clippingParam
			);
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::billboardMaterialHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_billboardMaterialHandle = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::cameraHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::centerRate(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_centerRate = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::blendRate(const tktkMath::Color& value)
	{
		// 値を設定して自身の参照を返す
		m_blendRate = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::clippingLeftTopPos(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_clippingParam.leftTopPos = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::clippingSize(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_clippingParam.size = value;
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::billboardMaterialIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_billboardMaterialHandle = DX12GameManager::getBillboardMaterialHandle(value);
		return *this;
	}

	BillboardClippingDrawerMaker& BillboardClippingDrawerMaker::cameraIdImpl(int value)
	{
		// 値を設定して自身の参照を返す
		m_cameraHandle = DX12GameManager::getCameraHandle(value);
		return *this;
	}
}