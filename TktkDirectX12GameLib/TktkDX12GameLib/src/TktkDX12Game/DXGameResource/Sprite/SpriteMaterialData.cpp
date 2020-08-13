#include "TktkDX12Game/DXGameResource/Sprite/SpriteMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Sprite/SpriteConstantBufferData.h"

namespace tktk
{
	SpriteMaterialData::SpriteMaterialData(const SpriteMaterialInitParam& initParam)
		: m_createDescriptorHeapId(initParam.createDescriptorHeapId)
		, m_blendRate(initParam.blendRate)
		, m_textureUvOffset(initParam.textureUvOffset)
		, m_textureUvMulRate(initParam.textureUvMulRate)
		, m_spriteCenterRate(initParam.spriteCenterRate)
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		{ /* シェーダーリソースビューのディスクリプタの情報 */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// スプライトテクスチャの１種類
			srvDescriptorParam.descriptorParamArray = {
				{ initParam.srvBufferType, initParam.useBufferId }
			};
		}

		{ /* コンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// スプライト定数バッファの１種類
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemId(SystemCBufferType::Sprite) }
			};
		}

		tktkMath::Vector3 textureBufferSize = tktkMath::Vector3_v::zero;

		switch (initParam.srvBufferType)
		{
		case BufferType::texture:

			textureBufferSize = DX12GameManager::getTextureBufferSizePx(initParam.useBufferId);
			m_textureSize = { textureBufferSize.x, textureBufferSize.y };
			break;

		case BufferType::renderTarget:

			m_textureSize = DX12GameManager::getRtBufferSizePx(initParam.useBufferId);
			break;

		case BufferType::depthStencil:

			m_textureSize = DX12GameManager::getDsBufferSizePx(initParam.useBufferId);
			break;
		}

		DX12GameManager::createBasicDescriptorHeap(m_createDescriptorHeapId, descriptorHeapInitParam);
	}

	void SpriteMaterialData::drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// スプライト用の定数バッファを更新する
		updateSpriteConstantBuffer(drawFuncArgs.worldMatrix);

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

		// スプライト用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::Sprite));

		// ブレンドファクターを設定する
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// スプライト用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapId} });

		// トライアングルストリップで描画を行う
		DX12GameManager::setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// スプライト用の頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemId(SystemVertexBufferType::Sprite));

		// スプライト用のインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemId(SystemIndexBufferType::Sprite));

		// ドローコール
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapId != DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapId, 0U, 1U);
		}
	}

	// スプライト用の定数バッファを更新する
	void SpriteMaterialData::updateSpriteConstantBuffer(const tktkMath::Matrix3& worldMatrix) const
	{
		SpriteConstantBufferData constantBufferData;
		for (unsigned int i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			constantBufferData.worldMatrix[i] = worldMatrix.m[i / 4U][i % 4U];
		}
		constantBufferData.blendRate = m_blendRate;
		constantBufferData.textureUvOffset = m_textureUvOffset;
		constantBufferData.textureUvMulRate = m_textureUvMulRate;
		constantBufferData.textureSize = m_textureSize;
		constantBufferData.spriteCenterRate = m_spriteCenterRate;
		constantBufferData.screenSize = DX12GameManager::getWindowSize();

		DX12GameManager::updateCBuffer(DX12GameManager::getSystemId(SystemCBufferType::Sprite), constantBufferData);
	}
}