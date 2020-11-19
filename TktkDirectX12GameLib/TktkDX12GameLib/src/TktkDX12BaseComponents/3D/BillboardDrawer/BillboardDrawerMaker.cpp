#include "TktkDX12BaseComponents/3D/BillboardDrawer/BillboardDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	BillboardDrawerMaker BillboardDrawerMaker::m_self;

	BillboardDrawerMaker& BillboardDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BillboardDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<BillboardDrawer> BillboardDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<BillboardDrawer>(
			m_billboardMaterialHandle,
			m_centerRate,
			m_blendRate,
			m_clippingLeftTopPos,
			m_clippingSize
			);
	}

	BillboardDrawerMaker& BillboardDrawerMaker::billboardMaterialHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_billboardMaterialHandle = value;
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

	BillboardDrawerMaker& BillboardDrawerMaker::clippingLeftTopPos(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_clippingLeftTopPos = value;
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::notClippingUseHandle(size_t billboarddMaterialHandle)
	{
		// ビルボードハンドルからテクスチャサイズを取得し、クリッピングサイズに設定する
		const auto& textureSize = DX12GameManager::getBillboardTextureSize(billboarddMaterialHandle);
		m_clippingSize = { textureSize.x, textureSize.y };
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::notClippingUseId(ResourceIdCarrier billboarddMaterialId)
	{
		// ビルボードIdからテクスチャサイズを取得し、クリッピングサイズに設定する
		const auto& textureSize = DX12GameManager::getBillboardTextureSize(DX12GameManager::getBillboardMaterialHandle(billboarddMaterialId));
		m_clippingSize = { textureSize.x, textureSize.y };
		return *this;
	}

	BillboardDrawerMaker& BillboardDrawerMaker::clippingSize(const tktkMath::Vector2& value)
	{
		// 値を設定して自身の参照を返す
		m_clippingSize = value;
		return *this;
	}
}