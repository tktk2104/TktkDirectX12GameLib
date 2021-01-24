#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Line2D/Line2DMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Line2D/Structs/Line2DMaterialDrawFuncArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Line2D/Structs/Line2DCBufferData.h"

namespace tktk
{
	Line2DMaterialData::Line2DMaterialData()
	{
		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadCbufferHandle			= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Line2D), Line2DCBufferData()));
		m_createdUploadVertexBufferHandle	= DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::vertex, DX12GameManager::getSystemHandle(SystemVertexBufferType::Line2D), std::vector<tktkMath::Vector2>(256U)));
	}

	Line2DMaterialData::~Line2DMaterialData()
	{
		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadCbufferHandle);
		DX12GameManager::eraseUploadBuffer(m_createdUploadVertexBufferHandle);
	}

	Line2DMaterialData::Line2DMaterialData(Line2DMaterialData&& other) noexcept
		: m_createUploadCbufferHandle(other.m_createUploadCbufferHandle)
		, m_createdUploadVertexBufferHandle(other.m_createdUploadVertexBufferHandle)
	{
		other.m_createUploadCbufferHandle		= 0U;
		other.m_createdUploadVertexBufferHandle = 0U;
	}

	void Line2DMaterialData::drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs)
	{
		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		Line2DCBufferData cbufferData{};
		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			cbufferData.worldMatrix[i] = drawFuncArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		cbufferData.lineColor = drawFuncArgs.lineColor;
		cbufferData.screenSize = DX12GameManager::getDrawGameAreaSize();
		DX12GameManager::updateUploadBuffer(m_createUploadCbufferHandle, CopySourceDataCarrier(cbufferData, 0U));

		// 頂点バッファのコピー用バッファを更新する
		// TODO : 前フレームと頂点バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(m_createdUploadVertexBufferHandle, CopySourceDataCarrier(sizeof(tktkMath::Vector2) * drawFuncArgs.lineVertexArray.size(), drawFuncArgs.lineVertexArray.data(), 0U));

		// ライン用の定数バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadCbufferHandle);

		// ライン用の頂点バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createdUploadVertexBufferHandle);

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
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::LineStrip);

		// 自身の頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Line2D));
		
		// ドローコール
		DX12GameManager::drawInstanced(drawFuncArgs.lineVertexArray.size(), 1U, 0U, 0U);
		
		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}
	}
}