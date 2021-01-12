#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/SpriteMaterialData.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteMaterialDrawFuncArgs.h"

namespace tktk
{
	SpriteMaterialData::SpriteMaterialData(const SpriteMaterialInitParam& initParam)
		: m_maxInstanceCount(initParam.maxInstanceCount)
	{
		// ディスクリプタヒープを作る
		BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		descriptorHeapInitParam.shaderVisible = true;
		descriptorHeapInitParam.descriptorTableParamArray.resize(2U);

		{ /* シェーダーリソースビューのディスクリプタの情報 */
			auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

			// スプライトテクスチャの１種類
			srvDescriptorParam.descriptorParamArray = { { initParam.srvBufferType, initParam.useBufferHandle } };
		}

		{ /* コンスタントバッファービューのディスクリプタの情報 */
			auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
			cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

			// スクリーンサイズバッファの１種類
			cbufferViewDescriptorParam.descriptorParamArray = { { BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::DrawGameAreaSize) } };
		}

		// switch文の中で変数宣言できない事の弊害
		const tktkMath::Vector3* textureBufferSize = nullptr;

		switch (initParam.srvBufferType)
		{
		case BufferType::texture:

			textureBufferSize = &DX12GameManager::getTextureBufferSizePx(initParam.useBufferHandle);
			m_textureSize = { textureBufferSize->x, textureBufferSize->y };
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
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(std::vector<SpriteMaterialInstanceData>(m_maxInstanceCount));
	}

	SpriteMaterialData::~SpriteMaterialData()
	{
		// 作ったディスクリプタヒープを削除する
		DX12GameManager::eraseBasicDescriptorHeap(m_createDescriptorHeapHandle);
	}

	SpriteMaterialData::SpriteMaterialData(SpriteMaterialData&& other) noexcept
		: m_createDescriptorHeapHandle(other.m_createDescriptorHeapHandle)
		, m_maxInstanceCount(other.m_maxInstanceCount)
		, m_textureSize(other.m_textureSize)
	{
		other.m_createDescriptorHeapHandle = 0U;
	}

	const tktkMath::Vector2& SpriteMaterialData::getSpriteTextureSize() const
	{
		return m_textureSize;
	}

	size_t SpriteMaterialData::getMaxInstanceCount() const
	{
		return m_maxInstanceCount;
	}

	size_t SpriteMaterialData::getCurInstanceCount() const
	{
		return m_instanceCount;
	}

	void SpriteMaterialData::clearInstanceParam()
	{
		// インスタンス情報のリストをクリアする
		m_instanceParamList.clear();

		// インスタンス数を初期化する
		m_instanceCount = 0U;
	}

	void SpriteMaterialData::addInstanceParam(float drawPriority, const TempSpriteMaterialInstanceData& instanceParam)
	{
		// インスタンス数の上限に達していた場合、強制終了
		if (m_instanceCount == m_maxInstanceCount) return;

		SpriteMaterialInstanceData spriteInstanceParam;

		for (size_t i = 0; i < 12; i++)
		{
			if (i % 4U == 3) continue;
			spriteInstanceParam.worldMatrix[i] = instanceParam.worldMatrix.m[i / 4U][i % 4U];
		}

		spriteInstanceParam.textureSize			= instanceParam.texturePixelCount;
		spriteInstanceParam.textureUvOffset		= { instanceParam.texturePixelOffset.x		/ m_textureSize.x,	instanceParam.texturePixelOffset.y		/ m_textureSize.y };
		spriteInstanceParam.textureUvMulRate	= { instanceParam.texturePixelCount.x		/ m_textureSize.x,	instanceParam.texturePixelCount.y		/ m_textureSize.y };
		spriteInstanceParam.textureUvMulRate	= tktkMath::Vector2::scale(spriteInstanceParam.textureUvMulRate, instanceParam.textureUvMulRate);
		spriteInstanceParam.textureCenterRate	= instanceParam.textureCenterRate;
		spriteInstanceParam.blendRate			= instanceParam.blendRate;

		// インスタンス描画用の頂点バッファをリストに追加する
		m_instanceParamList.emplace(drawPriority, spriteInstanceParam);

		// インスタンス数をインクリメント
		m_instanceCount++;
	}

	void SpriteMaterialData::updateInstanceParam()
	{
		// もし、インスタンス描画用の値が設定されていなければ何もしない
		if (m_instanceCount == 0U) return;

		auto vertBufferData = std::vector<SpriteMaterialInstanceData>(m_maxInstanceCount);

		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceVertParam : m_instanceParamList)
		{
			// インデックスがオーバーフローしたら強制終了
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// インスタンス描画用の頂点バッファ情報をコピーする
			vertBufferData.at(curIndex) = instanceVertParam.second;

			// インデックスをデクリメント
			--curIndex;
		}

		// 正しく全ての情報を代入できていなければ強制終了
		if (curIndex != std::numeric_limits<size_t>::max()) return;

		// インスタンス描画用の頂点バッファを更新する
		DX12GameManager::updateVertexBuffer(m_instanceParamVertexBufferHandle, vertBufferData);
	}

	void SpriteMaterialData::draw(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const
	{
		// もし、インスタンス描画用の値が設定されていなければ何もしない
		if (m_instanceCount == 0U) return;

		// ビューポートを設定する
		DX12GameManager::setViewport(drawFuncArgs.viewportHandle);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(drawFuncArgs.scissorRectHandle);

		// トライアングルストリップで描画を行う
		DX12GameManager::setPrimitiveTopology(PrimitiveTopology::TriangleStrip);

		// スプライト用の頂点バッファを設定する
		DX12GameManager::setVertexBuffer(DX12GameManager::getSystemHandle(SystemVertexBufferType::Sprite), m_instanceParamVertexBufferHandle);

		// スプライト用のインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(DX12GameManager::getSystemHandle(SystemIndexBufferType::Sprite));

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

		// ドローコール
		DX12GameManager::drawIndexedInstanced(4U, m_instanceCount, 0U, 0U, 0U);

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (drawFuncArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(drawFuncArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}
	}
}