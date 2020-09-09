#include "TktkDX12Game/DXGameResource/Line2D/Line2DMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Line2D/Line2DConstantBufferData.h"

namespace tktk
{
	Line2DMaterialData::Line2DMaterialData()
	{
		// コピー用バッファを作り、そのハンドルを取得する
		m_createCopyCbufferHandle = DX12GameManager::createCopyBuffer(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Line2D), Line2DConstantBufferData());
	}

	Line2DMaterialData::~Line2DMaterialData()
	{
		// 作成した頂点バッファを削除する
		// ※１度も描画処理が呼ばれなかった場合は何もしない
		DX12GameManager::eraseVertexBuffer(m_createdVertexBufferHandle);

		// コピー用バッファを削除する
		DX12GameManager::eraseCopyBuffer(m_createCopyCbufferHandle);
	}

	Line2DMaterialData::Line2DMaterialData(Line2DMaterialData&& other) noexcept
		: m_createdVertexBufferHandle(other.m_createdVertexBufferHandle)
		, m_createCopyCbufferHandle(other.m_createCopyCbufferHandle)
	{
		other.m_createdVertexBufferHandle	= 0U;
		other.m_createCopyCbufferHandle		= 0U;
	}

	void Line2DMaterialData::drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		// 前フレームで作成した頂点バッファを削除する
		// ※初回実行時は何もしない
		DX12GameManager::eraseVertexBuffer(m_createdVertexBufferHandle);

		// 自身の頂点バッファを作る
		m_createdVertexBufferHandle = DX12GameManager::createVertexBuffer(drawFuncArgs.lineVertexArray);

		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		updateCopyCbuffer(drawFuncArgs);

		// ライン用の定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createCopyCbufferHandle);

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

		// ライン用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::Line2D));

		// ブレンドファクターを設定する
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// 自身のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::Line2D)} });
		
		// ラインストリップで描画を行う
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);

		// 自身の頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_createdVertexBufferHandle);
		
		// ドローコール
#ifdef _M_AMD64 /* x64ビルドなら */
		DX12GameManager::drawInstanced(static_cast<unsigned int>(drawFuncArgs.lineVertexArray.size()), 1U, 0U, 0U);
#else
		DX12GameManager::drawInstanced(drawFuncArgs.lineVertexArray.size(), 1U, 0U, 0U);
#endif // _M_AMD64
		
		

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}
	}

	// 定数バッファのコピー用バッファを更新する
	void Line2DMaterialData::updateCopyCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const
	{
		Line2DConstantBufferData cbufferData{};
		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			cbufferData.worldMatrix[i] = drawFuncArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		cbufferData.lineColor = drawFuncArgs.lineColor;
		cbufferData.screenSize = DX12GameManager::getWindowSize();

		DX12GameManager::updateCopyBuffer(m_createCopyCbufferHandle, cbufferData);
	}
}