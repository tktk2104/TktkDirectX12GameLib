#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Mesh/BasicMeshData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshData::BasicMeshData(const BasicMeshInitParam& initParam)
		: m_useVertexBufferHandle(initParam.useVertexBufferHandle)
		, m_useIndexBufferHandle(initParam.useIndexBufferHandle)
		, m_indexNum(initParam.indexNum)
		, m_primitiveTopology(initParam.primitiveTopology)
		, m_materialSlots(initParam.materialSlots)
	{
		
	}

	BasicMeshData::BasicMeshData(const BasicMeshData& other)
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(other.m_materialSlots)
	{
		
	}

	BasicMeshData::BasicMeshData(BasicMeshData&& other) noexcept
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(std::move(other.m_materialSlots))
	{
	}

	void BasicMeshData::setMaterialHandle(size_t materialSlot, size_t materialHandle)
	{
		m_materialSlots.at(materialSlot).useMaterialHandle = materialHandle;
	}

	void BasicMeshData::writeShadowMap() const
	{
		// シャドウマップ描画用の深度バッファー“のみ”を設定する
		DX12GameManager::setOnlyDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));

		// ビューポートを設定する
		DX12GameManager::setViewport(DX12GameManager::getSystemHandle(SystemViewportType::Basic));

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(DX12GameManager::getSystemHandle(SystemScissorRectType::Basic));

		// 通常メッシュ版シャドウマップ描画用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::ShadowMap));

		// 通常メッシュ版シャドウマップ描画用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::BasicMeshShadowMap) } });

		// 指定のトポロジーで描画を行う
		DX12GameManager::setPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(m_primitiveTopology));

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle);

		// 描画で使用するインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// ドローコール
		DX12GameManager::drawIndexedInstanced(m_indexNum, 1U, 0U, 0U, 0U);

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));
	}

	void BasicMeshData::drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// ビューポートを設定する
		DX12GameManager::setViewport(baseArgs.viewportHandle);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);

		// 指定のトポロジーで描画を行う
		DX12GameManager::setPrimitiveTopology(static_cast<D3D_PRIMITIVE_TOPOLOGY>(m_primitiveTopology));

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle);

		// 描画で使用するインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// レンダーターゲットと深度ステンシルを設定する（バックバッファーに直で描画する場合は特殊処理）
		if (baseArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferViewAndDsv(baseArgs.dsvDescriptorHeapHandle);
		}
		else
		{
			DX12GameManager::setRtvAndDsv(baseArgs.rtvDescriptorHeapHandle, baseArgs.dsvDescriptorHeapHandle, 0U, 1U);
		}

		// マテリアルの数だけ描画する
		for (const auto& node : m_materialSlots)
		{
			// マテリアルの情報を設定する
			DX12GameManager::setMaterialData(node.useMaterialHandle);

			// ドローコール
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, 1U, node.indexBufferStartPos, 0U, 0U);
		}

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (baseArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(baseArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDsv(baseArgs.dsvDescriptorHeapHandle);
	}
}