#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteTransformCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialCbufferData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialDrawFuncArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteCbufferUpdateFuncArgs.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteClippingParam.h"

namespace tktk
{
	SpriteMaterialData::SpriteMaterialData(const SpriteMaterialInitParam& initParam)
		: m_blendRate(initParam.blendRate)
		, m_textureUvOffset(initParam.textureUvOffset)
		, m_textureUvMulRate(initParam.textureUvMulRate)
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

		{ /* シェーダーリソースビューのディスクリプタの情報 */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// スプライトテクスチャの１種類
			srvDescriptorParam.descriptorParamArray = {
				{ initParam.srvBufferType, initParam.useBufferHandle }
			};
		}

		{ /* コンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// マテリアル定数バッファと座標変換定数バッファの２種類
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::SpriteMaterialManager) },
				{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::SpriteTransform) }
			};
		}

		{ /* コンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// マテリアル定数バッファの１種類
			cbufferViewDescriptorParam.descriptorParamArray = {
				{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::SpriteMaterialManager) }
			};
		}

		tktkMath::Vector3 textureBufferSize = tktkMath::Vector3_v::zero;

		switch (initParam.srvBufferType)
		{
		case BufferType::texture:

			textureBufferSize = DX12GameManager::getTextureBufferSizePx(initParam.useBufferHandle);
			m_textureSize = { textureBufferSize.x, textureBufferSize.y };
			break;

		case BufferType::renderTarget:

			m_textureSize = DX12GameManager::getRtBufferSizePx(initParam.useBufferHandle);
			break;

		case BufferType::depthStencil:

			m_textureSize = DX12GameManager::getDsBufferSizePx(initParam.useBufferHandle);
			break;
		}

		m_createDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::SpriteMaterialManager), SpriteMaterialCbufferData()));
	}

	SpriteMaterialData::~SpriteMaterialData()
	{
		// 作ったディスクリプタヒープを削除する
		DX12GameManager::eraseBasicDescriptorHeap(m_createDescriptorHeapHandle);

		// アップロード用バッファを削除する
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	SpriteMaterialData::SpriteMaterialData(SpriteMaterialData&& other) noexcept
		: m_createDescriptorHeapHandle(other.m_createDescriptorHeapHandle)
		, m_createUploadBufferHandle(other.m_createUploadBufferHandle)
		, m_blendRate(other.m_blendRate)
		, m_textureUvOffset(other.m_textureUvOffset)
		, m_textureUvMulRate(other.m_textureUvMulRate)
		, m_textureSize(other.m_textureSize)
	{
		other.m_createDescriptorHeapHandle = 0U;
		other.m_createUploadBufferHandle = 0U;
	}

	void SpriteMaterialData::drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		updateCopyBuffer();

		// スプライト用定数バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadBufferHandle);

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

		// スプライト用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::Sprite));

		// ブレンドファクターを設定する
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// スプライト用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapHandle} });

		// トライアングルストリップで描画を行う
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// スプライト用の頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite));

		// スプライト用のインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

		// ドローコール
		DX12GameManager::drawIndexedInstanced(4U, 1U, 0U, 0U, 0U);

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}
	}

	void SpriteMaterialData::updateTransformCbuffer(size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs) const
	{
		// スプライトの座標変換用定数バッファ形式
		SpriteTransformCbuffer transformBufferData{};

		for (size_t i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			transformBufferData.worldMatrix[i] = cbufferUpdateArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		transformBufferData.textureUvOffset		= m_textureUvOffset;
		transformBufferData.textureUvMulRate	= m_textureUvMulRate;
		transformBufferData.textureSize			= m_textureSize;
		transformBufferData.spriteCenterRate	= cbufferUpdateArgs.spriteCenterRate;

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

		// 座標変換用の定数バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(copyBufferHandle);
	}

	void SpriteMaterialData::updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const
	{
		// スプライトの座標変換用定数バッファ形式
		SpriteTransformCbuffer transformBufferData{};

		for (size_t i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			transformBufferData.worldMatrix[i] = cbufferUpdateArgs.worldMatrix.m[i / 4U][i % 4U];
		}
		transformBufferData.textureUvOffset		= tktkMath::Vector2(clippingParam.leftTopPos.x / m_textureSize.x, clippingParam.leftTopPos.y / m_textureSize.y) + m_textureUvOffset;
		transformBufferData.textureUvMulRate	= tktkMath::Vector2(clippingParam.size.x / m_textureSize.x * m_textureUvMulRate.x, clippingParam.size.y / m_textureSize.y * m_textureUvMulRate.y);
		transformBufferData.textureSize			= clippingParam.size;
		transformBufferData.spriteCenterRate	= cbufferUpdateArgs.spriteCenterRate;

		// 定数バッファのアップロード用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

		// 座標変換用の定数バッファにアップロードバッファの情報をコピーする
		DX12GameManager::copyBuffer(copyBufferHandle);
	}

	// 定数バッファのアップロード用バッファを更新する
	void SpriteMaterialData::updateCopyBuffer() const
	{
		SpriteMaterialCbufferData constantBufferData;
		constantBufferData.blendRate		= m_blendRate;
		constantBufferData.screenSize		= DX12GameManager::getWindowSize();

		DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, constantBufferData);
	}
}