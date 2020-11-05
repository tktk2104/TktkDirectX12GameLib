#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialAppendParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(size_t cbufferHandle, size_t dataSize, void* dataTopPos)
		: m_cbufferHandle(cbufferHandle)
		, m_dataSize(dataSize)
	{
		m_dataTopPos = std::shared_ptr<void>(dataTopPos);

		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer({ BufferType::constant, m_cbufferHandle, dataSize, dataTopPos });
	}

	BasicMeshMaterialAppendParam::~BasicMeshMaterialAppendParam()
	{
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(BasicMeshMaterialAppendParam&& other) noexcept
		: m_createUploadBufferHandle(other.m_createUploadBufferHandle)
		, m_cbufferHandle(other.m_cbufferHandle)
		, m_dataSize(other.m_dataSize)
		, m_dataTopPos(std::move(other.m_dataTopPos))
	{
		other.m_createUploadBufferHandle = 0U;
	}

	void BasicMeshMaterialAppendParam::updateParam(size_t dataSize, const void* dataTopPos)
	{
		if (m_dataSize == dataSize) memcpy(m_dataTopPos.get(), dataTopPos, dataSize);
	}

	void BasicMeshMaterialAppendParam::updateCbuffer() const
	{
		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		updateCopyBuffer();

		// 定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadBufferHandle);
	}

	void BasicMeshMaterialAppendParam::updateCopyBuffer() const
	{
		DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, CopySourceDataCarrier(m_dataSize, m_dataTopPos.get()));
	}
}