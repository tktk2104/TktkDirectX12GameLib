#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardDrawFuncBaseArgs.h"

namespace tktk
{
	BillboardMaterialData::BillboardMaterialData(const BillboardMaterialInitParam& initParam)
		: m_maxInstanceCount(initParam.maxInstanceCount)
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		{ /* シェーダーリソースビューのディスクリプタの情報 */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// ビルボードテクスチャの１種類
			srvDescriptorParam.descriptorParamArray = { { initParam.srvBufferType, initParam.useBufferHandle } };
		}

		{ /* コンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// カメラバッファの１種類
			cbufferViewDescriptorParam.descriptorParamArray = { { BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera) } };
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


		// インスタンス描画用の頂点バッファを作る
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(std::vector<BillboardMaterialInstanceVertData>(m_maxInstanceCount));
	}

	BillboardMaterialData::~BillboardMaterialData()
	{
		// 作ったディスクリプタヒープを削除する
		DX12GameManager::eraseBasicDescriptorHeap(m_createDescriptorHeapHandle);
	}

	BillboardMaterialData::BillboardMaterialData(BillboardMaterialData&& other) noexcept
		: m_createDescriptorHeapHandle(other.m_createDescriptorHeapHandle)
		, m_maxInstanceCount(other.m_maxInstanceCount)
		, m_textureSize(other.m_textureSize)
	{
		other.m_createDescriptorHeapHandle = 0U;
	}

	const tktkMath::Vector2& BillboardMaterialData::getBillboardTextureSize() const
	{
		return m_textureSize;
	}

	void BillboardMaterialData::clearInstanceParam()
	{
		// インスタンス情報のリストをクリアする
		m_instanceVertParamList.clear();

		// インスタンス数を初期化する
		m_instanceCount = 0U;
	}

	void BillboardMaterialData::addInstanceVertParam(const BillboardMaterialInstanceVertData& instanceParam)
	{
		// インスタンス数の上限に達していた場合、強制終了
		if (m_instanceCount == m_maxInstanceCount) return;

		auto tempInstanceParam = instanceParam;
		tempInstanceParam.textureSize = m_textureSize;
		tempInstanceParam.textureUvOffset = { tempInstanceParam.textureUvOffset.x / m_textureSize.x,	tempInstanceParam.textureUvOffset.y / m_textureSize.y };
		tempInstanceParam.textureUvMulRate = { tempInstanceParam.textureUvMulRate.x / m_textureSize.x,	tempInstanceParam.textureUvMulRate.y / m_textureSize.y };
		
		// インスタンス描画用の頂点バッファをリストに追加する
		m_instanceVertParamList.push_front(tempInstanceParam);

		// インスタンス数をインクリメント
		m_instanceCount++;
	}

	void BillboardMaterialData::updateInstanceParamVertBuffer() const
	{
		auto vertBufferData = std::vector<BillboardMaterialInstanceVertData>(m_maxInstanceCount);
	
		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceVertParam : m_instanceVertParamList)
		{
			// インデックスがオーバーフローしたら強制終了
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// インスタンス描画用の頂点バッファ情報をコピーする
			vertBufferData.at(curIndex) = instanceVertParam;

			// インデックスをデクリメント
			--curIndex;
		}

		// 正しく全ての情報を代入できていなければ強制終了
		if (curIndex != std::numeric_limits<size_t>::max()) return;
	
		// インスタンス描画用の頂点バッファを更新する
		DX12GameManager::updateVertexBuffer(m_instanceParamVertexBufferHandle, vertBufferData);
	}

	void BillboardMaterialData::draw(const BillboardDrawFuncBaseArgs& drawFuncArgs) const
	{
		// もし、インスタンス描画用の値が設定されていなければ何もしない
		if (m_instanceCount == 0U) return;

		// インスタンス描画情報を扱う頂点バッファを更新する
		updateInstanceParamVertBuffer();

		// ビューポートを設定する
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// トライアングルストリップで描画を行う
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// ビルボード用の頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite), m_instanceParamVertexBufferHandle);

		// ビルボード用のインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

		// レンダーターゲットと深度ステンシルを設定する（バックバッファーに直で描画する場合は特殊処理）
		if (drawFuncArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::setBackBufferViewAndDsv(drawFuncArgs.dsvDescriptorHeapHandle);
		}
		else
		{
			DX12GameManager::setRtvAndDsv(drawFuncArgs.rtvDescriptorHeapHandle, drawFuncArgs.dsvDescriptorHeapHandle, 0U, 1U);
		}

		// ビルボード用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::Billboard));

		// ブレンドファクターを設定する
		DX12GameManager::setBlendFactor({ 1.0f, 1.0f, 1.0f, 1.0f });

		// ビルボード用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, m_createDescriptorHeapHandle} });

		// ドローコール
		DX12GameManager::drawIndexedInstanced(4U, m_instanceCount, 0U, 0U, 0U);

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDsv(drawFuncArgs.dsvDescriptorHeapHandle);
	}

	//void BillboardMaterialData::updateTransformCbuffer(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const
	//{
	//	// ビルボードの座標変換用定数バッファ形式
	//	BillboardCbufferData transformBufferData{};

	//	transformBufferData.billboardPosition	= updateArgs.billboardPosition;
	//	transformBufferData.billboardAngle		= updateArgs.billboardAngle;
	//	transformBufferData.billboardScale		= updateArgs.billboardScale;
	//	transformBufferData.textureUvOffset		= tktkMath::Vector2_v::zero;
	//	transformBufferData.textureUvMulRate	= tktkMath::Vector2_v::one;
	//	transformBufferData.textureSize			= m_textureSize;
	//	transformBufferData.textureCenterRate	= updateArgs.textureCenterRate;
	//	transformBufferData.viewMatrix			= updateArgs.viewMatrix;
	//	transformBufferData.projectionMatrix	= updateArgs.projectionMatrix;
	//	transformBufferData.blendRate			= updateArgs.blendRate;

	//	// 定数バッファのアップロード用バッファを更新する
	//	// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
	//	DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

	//	// 座標変換用の定数バッファにコピーバッファの情報をコピーする
	//	DX12GameManager::copyBuffer(copyBufferHandle);
	//}

	//void BillboardMaterialData::updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const
	//{
	//	// ビルボードの座標変換用定数バッファ形式
	//	BillboardCbufferData transformBufferData{};

	//	transformBufferData.billboardPosition	= updateArgs.billboardPosition;
	//	transformBufferData.billboardAngle		= updateArgs.billboardAngle;
	//	transformBufferData.billboardScale		= updateArgs.billboardScale;
	//	transformBufferData.textureUvOffset		= tktkMath::Vector2(clippingParam.leftTopPos.x / m_textureSize.x,	clippingParam.leftTopPos.y / m_textureSize.y) +
	//	transformBufferData.textureUvMulRate	= tktkMath::Vector2(clippingParam.size.x / m_textureSize.x,			clippingParam.size.y / m_textureSize.y);
	//	transformBufferData.textureSize			= clippingParam.size;
	//	transformBufferData.textureCenterRate	= updateArgs.textureCenterRate;
	//	transformBufferData.viewMatrix			= updateArgs.viewMatrix;
	//	transformBufferData.projectionMatrix	= updateArgs.projectionMatrix;
	//	transformBufferData.blendRate			= updateArgs.blendRate;

	//	// 定数バッファのアップロード用バッファを更新する
	//	// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
	//	DX12GameManager::updateUploadBuffer(copyBufferHandle, transformBufferData);

	//	// 座標変換用の定数バッファにコピーバッファの情報をコピーする
	//	DX12GameManager::copyBuffer(copyBufferHandle);
	//}
}