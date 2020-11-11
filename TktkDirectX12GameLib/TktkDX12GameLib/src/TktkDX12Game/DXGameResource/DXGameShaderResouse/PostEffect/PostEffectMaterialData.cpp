#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialDrawFuncArgs.h"

namespace tktk
{
	PostEffectMaterialData::PostEffectMaterialData(const PostEffectMaterialInitParam& initParam)
		: m_usePipeLineStateHandle(initParam.usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(initParam.useDescriptorHeapHandle)
		, m_autoClearRtvDescriptorHeapHandleArray(initParam.autoClearRtvDescriptorHeapHandleArray)
	{
	}

	PostEffectMaterialData::PostEffectMaterialData(PostEffectMaterialData&& other) noexcept
		: m_usePipeLineStateHandle(other.m_usePipeLineStateHandle)
		, m_useDescriptorHeapHandle(other.m_useDescriptorHeapHandle)
		, m_autoClearRtvDescriptorHeapHandleArray(std::move(other.m_autoClearRtvDescriptorHeapHandleArray))
	{
	}

	void PostEffectMaterialData::drawPostEffect(const PostEffectMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// ビューポートを設定する
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// レンダーターゲットを設定する（バックバッファーに直で描画する場合は特殊処理）
		if (drawFuncArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferView();
		}
		else
		{
			DX12GameManager::setRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// 描画で使用するパイプラインステートを設定する
		DX12GameManager::setPipeLineState(m_usePipeLineStateHandle);

		// 描画で使用するディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_useDescriptorHeapHandle} });

		// トライアングルストリップで描画する
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// 板ポリゴンの頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite));

		// 板ポリゴンのインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

		// ドローコール
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// 描画後にクリアするレンダーターゲットビュー用のディスクリプタヒープのハンドルを巡回する
		for (const auto& node : m_autoClearRtvDescriptorHeapHandleArray)
		{
			DX12GameManager::setRtv(node, 0U, 1U);
			DX12GameManager::clearRtv(node, 0U);
			DX12GameManager::unSetRtv(node, 0U, 1U);
		}
	}
}