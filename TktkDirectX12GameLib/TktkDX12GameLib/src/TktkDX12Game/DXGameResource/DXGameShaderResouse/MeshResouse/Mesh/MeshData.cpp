#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/MeshData.h"

#include <limits>
#include <vector>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshDrawFuncBaseArgs.h"

namespace tktk
{
	MeshData::MeshData(const MeshInitParam& initParam)
		: m_useVertexBufferHandle(initParam.useVertexBufferHandle)
		, m_useIndexBufferHandle(initParam.useIndexBufferHandle)
		, m_indexNum(initParam.indexNum)
		, m_primitiveTopology(initParam.primitiveTopology)
		, m_materialSlots(initParam.materialSlots)
		, m_instanceVertParamTypeSize(initParam.instanceVertParam.typeSize)
		, m_maxInstanceCount(initParam.instanceVertParam.dataCount)
	{
		// インスタンス描画用の頂点バッファを作る
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(initParam.instanceVertParam);

		// 骨情報テクスチャ更新用のアップロードバッファを作る
		m_boneMatrixTextureBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(
			BufferType::texture,
			DX12GameManager::getSystemHandle(SystemTextureBufferType::MeshBoneMatrix),
			std::vector<unsigned char>(sizeof(tktkMath::Matrix4) * 128U * 128, 0U)
		));
	}

	MeshData::MeshData(const MeshData& other)
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(other.m_materialSlots)
		, m_instanceVertParamTypeSize(other.m_instanceVertParamTypeSize)
		, m_maxInstanceCount(other.m_maxInstanceCount)
	{
		// インスタンス描画用の頂点バッファ情報をバイナリ形式で書き込むメモリ領域を作る
		auto rawVertBufferData = std::vector<unsigned char>(m_instanceVertParamTypeSize * m_maxInstanceCount, 0U);

		// 頂点バッファの入れ物を作る
		auto vertBufferData = VertexDataCarrier(m_instanceVertParamTypeSize, m_maxInstanceCount, rawVertBufferData.data());

		// インスタンス描画用の頂点バッファを作る
		m_instanceParamVertexBufferHandle = DX12GameManager::createVertexBuffer(vertBufferData);

		// 骨情報テクスチャ更新用のアップロードバッファを作る
		m_boneMatrixTextureBufferHandle = DX12GameManager::createUploadBuffer(UploadBufferInitParam::create(
			BufferType::texture,
			DX12GameManager::getSystemHandle(SystemTextureBufferType::MeshBoneMatrix),
			std::vector<unsigned char>(sizeof(tktkMath::Matrix4) * 128U * 128)
		));
	}

	MeshData::MeshData(MeshData&& other) noexcept
		: m_useVertexBufferHandle(other.m_useVertexBufferHandle)
		, m_useIndexBufferHandle(other.m_useIndexBufferHandle)
		, m_instanceParamVertexBufferHandle(other.m_instanceParamVertexBufferHandle)
		, m_boneMatrixTextureBufferHandle(other.m_boneMatrixTextureBufferHandle)
		, m_indexNum(other.m_indexNum)
		, m_primitiveTopology(other.m_primitiveTopology)
		, m_materialSlots(std::move(other.m_materialSlots))
		, m_instanceVertParamTypeSize(other.m_instanceVertParamTypeSize)
		, m_maxInstanceCount(other.m_maxInstanceCount)
	{
		other.m_instanceParamVertexBufferHandle = 0U;
		other.m_boneMatrixTextureBufferHandle	= 0U;
	}

	void MeshData::setMaterialHandle(size_t materialSlot, size_t materialHandle)
	{
		m_materialSlots.at(materialSlot).useMaterialHandle = materialHandle;
	}

	void MeshData::clearInstanceParam()
	{
		// インスタンス情報のリストをクリアする
		m_instanceVertParamList.clear();
		m_instanceBoneMatrixList.clear();

		// インスタンス数を初期化する
		m_instanceCount = 0U;
	}

	void MeshData::addInstanceVertParam(const CopySourceDataCarrier& instanceParam)
	{
		// 不正なサイズの頂点バッファ情報が存在したら強制終了
		if (instanceParam.dataSize != m_instanceVertParamTypeSize) return;

		// インスタンス数の上限に達していた場合、強制終了
		if (m_instanceCount == m_maxInstanceCount) return;

		// インスタンス描画用の頂点バッファのバイナリデータをリストに追加する
		auto rawInstanceParam = std::vector<unsigned char>(instanceParam.dataSize, 0U);
		memcpy(rawInstanceParam.data(), instanceParam.dataTopPos, instanceParam.dataSize);
		m_instanceVertParamList.push_front(rawInstanceParam);

		// インスタンス数をインクリメント
		m_instanceCount++;
	}

	void MeshData::addInstanceBoneMatrix(const std::array<tktkMath::Matrix4, 128>& boneMatrix)
	{
		auto invertBoneMatrix = boneMatrix;

		for (auto& matrix : invertBoneMatrix)
		{
			matrix = tktkMath::Matrix4(
				matrix.m[0][0], matrix.m[1][0], matrix.m[2][0], matrix.m[3][0],
				matrix.m[0][1], matrix.m[1][1], matrix.m[2][1], matrix.m[3][1],
				matrix.m[0][2], matrix.m[1][2], matrix.m[2][2], matrix.m[3][2],
				matrix.m[0][3], matrix.m[1][3], matrix.m[2][3], matrix.m[3][3]
			);
		}

		m_instanceBoneMatrixList.push_front(invertBoneMatrix);
	}

	void MeshData::updateInstanceParamVertBuffer() const
	{
		// インスタンス描画用の頂点バッファ情報をバイナリ形式で書き込むメモリ領域を作る
		auto rawVertBufferData = std::vector<unsigned char>(m_instanceVertParamTypeSize * m_maxInstanceCount, 0U);

		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceVertParam : m_instanceVertParamList)
		{
			// インデックスがオーバーフローしたら強制終了
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// インスタンス描画用の頂点バッファ情報をバイナリ形式でコピーする
			memcpy(&rawVertBufferData.at(m_instanceVertParamTypeSize * curIndex), instanceVertParam.data(), m_instanceVertParamTypeSize);

			// インデックスをデクリメント
			--curIndex;
		}

		// 正しく全ての情報を代入できていなければ強制終了
		if (curIndex != std::numeric_limits<size_t>::max()) return;

		// 頂点バッファの入れ物を作る
		auto vertBufferData = VertexDataCarrier(m_instanceVertParamTypeSize, m_maxInstanceCount, rawVertBufferData.data());

		// インスタンス描画用の頂点バッファを更新する
		DX12GameManager::updateVertexBuffer(m_instanceParamVertexBufferHandle, vertBufferData);
	}

	void MeshData::updateBoneMatrixTextureBuffer() const
	{
		auto boneMatData = std::vector<unsigned char>(sizeof(tktkMath::Matrix4) * 128U * 128, 0U);

		size_t curIndex = m_instanceCount - 1U;

		for (const auto& instanceBoneMatrix : m_instanceBoneMatrixList)
		{
			// インデックスがオーバーフローしたら強制終了
			if (curIndex == std::numeric_limits<size_t>::max()) return;

			// インスタンス描画用の頂点バッファ情報をバイナリ形式でコピーする
			memcpy(&boneMatData.at(sizeof(tktkMath::Matrix4) * 128U * curIndex), instanceBoneMatrix.data(), sizeof(tktkMath::Matrix4) * 128U);

			// インデックスをデクリメント
			--curIndex;
		}

		// 正しく全ての情報を代入できていなければ強制終了
		if (curIndex != std::numeric_limits<size_t>::max()) return;

		DX12GameManager::updateUploadBuffer(m_boneMatrixTextureBufferHandle, CopySourceDataCarrier(boneMatData.size(), boneMatData.data()));
	}

	void MeshData::writeShadowMap() const
	{
		// もし、インスタンス描画用の値が設定されていなければ何もしない
		if (m_instanceCount == 0U) return;

		// インスタンス描画情報を扱う頂点バッファを更新する
		updateInstanceParamVertBuffer();

		// ビューポートを設定する
		DX12GameManager::setViewport(DX12GameManager::getSystemHandle(SystemViewportType::WriteShadow));

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(DX12GameManager::getSystemHandle(SystemScissorRectType::WriteShadow));

		// 指定のトポロジーで描画を行う
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

		// 描画で使用するインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// シャドウマップ描画用の深度バッファー“のみ”を設定する
		DX12GameManager::setOnlyDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));

		// シンプルメッシュ版シャドウマップ描画用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::SimpleMeshShadowMap));

		// シンプルメッシュ版シャドウマップ描画用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::SimpleMeshShadowMap) } });

		// ドローコール
		DX12GameManager::drawIndexedInstanced(m_indexNum, m_instanceCount, 0U, 0U, 0U);

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));
	}

	void MeshData::writeShadowMapUseBone() const
	{
		// もし、インスタンス描画用の値が設定されていなければ何もしない
		if (m_instanceCount == 0U) return;

		// インスタンス描画情報を扱う頂点バッファを更新する
		updateInstanceParamVertBuffer();

		// インスタンス描画の骨行列のテクスチャを更新する
		updateBoneMatrixTextureBuffer();

		// 骨情報のテクスチャバッファを更新する
		DX12GameManager::copyBuffer(m_boneMatrixTextureBufferHandle);

		// ビューポートを設定する
		DX12GameManager::setViewport(DX12GameManager::getSystemHandle(SystemViewportType::WriteShadow));

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(DX12GameManager::getSystemHandle(SystemScissorRectType::WriteShadow));

		// 指定のトポロジーで描画を行う
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

		// 描画で使用するインデックスバッファを設定する
		DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);

		// シャドウマップ描画用の深度バッファー“のみ”を設定する
		DX12GameManager::setOnlyDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));

		// スキニングメッシュ版シャドウマップ描画用のパイプラインステートを設定する
		DX12GameManager::setPipeLineState(DX12GameManager::getSystemHandle(SystemPipeLineStateType::SkinningMeshShadowMap));

		// スキニングメッシュ版シャドウマップ描画用のディスクリプタヒープを設定する
		DX12GameManager::setDescriptorHeap({ { DescriptorHeapType::basic, DX12GameManager::getSystemHandle(SystemBasicDescriptorHeapType::SkinningMeshShadowMap) } });

		// ドローコール
		DX12GameManager::drawIndexedInstanced(m_indexNum, m_instanceCount, 0U, 0U, 0U);

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDsv(DX12GameManager::getSystemHandle(SystemDsvDescriptorHeapType::ShadowMap));
	}

	//void MeshData::drawMesh(const MeshDrawFuncBaseArgs& baseArgs) const
	//{
	//	// ビューポートを設定する
	//	DX12GameManager::setViewport(baseArgs.viewportHandle);
	//
	//	// シザー矩形を設定する
	//	DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);
	//
	//	// 指定のトポロジーで描画を行う
	//	DX12GameManager::setPrimitiveTopology(static_cast<PrimitiveTopology>(m_primitiveTopology));
	//
	//	// 描画で使用する頂点バッファを設定する
	//	DX12GameManager::setVertexBuffer(m_useVertexBufferHandle);
	//
	//	// 描画で使用するインデックスバッファを設定する
	//	DX12GameManager::setIndexBuffer(m_useIndexBufferHandle);
	//
	//	// レンダーターゲットと深度ステンシルを設定する（バックバッファーに直で描画する場合は特殊処理）
	//	if (baseArgs.rtvDescriptorHeapHandle == DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
	//	{
	//		DX12GameManager::setBackBufferViewAndDsv(baseArgs.dsvDescriptorHeapHandle);
	//	}
	//	else
	//	{
	//		DX12GameManager::setRtvAndDsv(baseArgs.rtvDescriptorHeapHandle, baseArgs.dsvDescriptorHeapHandle, 0U, 1U);
	//	}
	//
	//	// マテリアルの数だけ描画する
	//	for (const auto& node : m_materialSlots)
	//	{
	//		// マテリアルの情報を設定する
	//		DX12GameManager::setMaterialData(node.useMaterialHandle);
	//
	//		// ドローコール
	//		DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, 1U, node.indexBufferStartPos, 0U, 0U);
	//	}
	//
	//	// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
	//	if (baseArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
	//	{
	//		DX12GameManager::unSetRtv(baseArgs.rtvDescriptorHeapHandle, 0U, 1U);
	//	}
	//
	//	// 深度ステンシルバッファーをシェーダーで使える状態にする
	//	DX12GameManager::unSetDsv(baseArgs.dsvDescriptorHeapHandle);
	//}

	void MeshData::draw(const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// もし、インスタンス描画用の値が設定されていなければ何もしない
		if (m_instanceCount == 0U) return;

		// インスタンス描画情報を扱う頂点バッファを更新する
		updateInstanceParamVertBuffer();

		// ビューポートを設定する
		DX12GameManager::setViewport(baseArgs.viewportHandle);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);

		// 指定のトポロジーで描画を行う
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

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
			DX12GameManager::setMeshMaterialData(node.useMaterialHandle);

			// ドローコール
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, m_instanceCount, node.indexBufferStartPos, 0U, 0U);
		}

		// バックバッファ以外に描画していたら使用したレンダーターゲットバッファをシェーダーで使用する状態にする
		if (baseArgs.rtvDescriptorHeapHandle != DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer))
		{
			DX12GameManager::unSetRtv(baseArgs.rtvDescriptorHeapHandle, 0U, 1U);
		}

		// 深度ステンシルバッファーをシェーダーで使える状態にする
		DX12GameManager::unSetDsv(baseArgs.dsvDescriptorHeapHandle);
	}

	void MeshData::drawUseBone(const MeshDrawFuncBaseArgs& baseArgs) const
	{
		// もし、インスタンス描画用の値が設定されていなければ何もしない
		if (m_instanceCount == 0U) return;

		// インスタンス描画情報を扱う頂点バッファを更新する
		updateInstanceParamVertBuffer();

		// インスタンス描画の骨行列のテクスチャを更新する
		updateBoneMatrixTextureBuffer();

		// 骨情報のテクスチャバッファを更新する
		DX12GameManager::copyBuffer(m_boneMatrixTextureBufferHandle);

		// ビューポートを設定する
		DX12GameManager::setViewport(baseArgs.viewportHandle);

		// シザー矩形を設定する
		DX12GameManager::setScissorRect(baseArgs.scissorRectHandle);

		// 指定のトポロジーで描画を行う
		DX12GameManager::setPrimitiveTopology(m_primitiveTopology);

		// 描画で使用する頂点バッファを設定する
		DX12GameManager::setVertexBuffer(m_useVertexBufferHandle, m_instanceParamVertexBufferHandle);

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
			DX12GameManager::setMeshMaterialData(node.useMaterialHandle);

			// ドローコール
			DX12GameManager::drawIndexedInstanced(node.indexBufferUseCount, m_instanceCount, node.indexBufferStartPos, 0U, 0U);
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