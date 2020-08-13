#include "TktkDX12Game/DXGameResource/PostEffect/PostEffectMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	PostEffectMaterialData::PostEffectMaterialData(const PostEffectMaterialInitParam& initParam)
		: m_usePipeLineStateId(initParam.usePipeLineStateId)
		, m_useDescriptorHeapId(initParam.useDescriptorHeapId)
	{
	}

	void PostEffectMaterialData::drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// ビューポートを設定する
		DX12GameManager::setViewport(drawFuncArgs.viewportId);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectId);

		// レンダーターゲットを設定する（バックバッファーに直で描画する場合は特殊処理）
		if (drawFuncArgs.rtvDescriptorHeapId == DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}

		// 描画で使用するパイプラインステートを設定する
		DX12GameManager::setPipeLineState(m_usePipeLineStateId);

		// 描画で使用するディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_useDescriptorHeapId} });

		// トライアングルストリップで描画する
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// 板ポリゴンの頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Sprite));

		// 板ポリゴンのインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemId(SystemIndexBufferType::Sprite));

		// ドローコール
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}
	}
}