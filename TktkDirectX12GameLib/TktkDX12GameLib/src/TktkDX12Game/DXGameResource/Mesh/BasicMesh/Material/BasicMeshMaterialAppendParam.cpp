#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterialAppendParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos)
		: m_cbufferHandle(cbufferHandle)
		, m_dataSize(dataSize)
	{
		m_dataTopPos = std::shared_ptr<void>(dataTopPos);

		// コピー用バッファを作り、そのハンドルを取得する
		CopyBufferInitParam initParam{};
		initParam.targetBufferType		= BufferType::constant;
		initParam.targetBufferHandle	= m_cbufferHandle;
		initParam.bufferWidth = dataSize;
		initParam.dataTopPos = dataTopPos;
		m_createCopyBufferHandle = DX12GameManager::createCopyBufferImpl(initParam);
	}

	BasicMeshMaterialAppendParam::~BasicMeshMaterialAppendParam()
	{
		DX12GameManager::eraseCopyBuffer(m_createCopyBufferHandle);
	}

	BasicMeshMaterialAppendParam::BasicMeshMaterialAppendParam(BasicMeshMaterialAppendParam&& other) noexcept
		: m_createCopyBufferHandle(other.m_createCopyBufferHandle)
		, m_cbufferHandle(other.m_cbufferHandle)
		, m_dataSize(other.m_dataSize)
		, m_dataTopPos(std::move(other.m_dataTopPos))
	{
		other.m_createCopyBufferHandle = 0U;
	}

	void BasicMeshMaterialAppendParam::updateParam(unsigned int dataSize, const void* dataTopPos)
	{
		if (m_dataSize == dataSize) memcpy(m_dataTopPos.get(), dataTopPos, dataSize);
	}

	void BasicMeshMaterialAppendParam::updateCbuffer() const
	{
		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		updateCopyBuffer();

		// 定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createCopyBufferHandle);
	}

	void BasicMeshMaterialAppendParam::updateCopyBuffer() const
	{
		DX12GameManager::updateCopyBufferImpl(m_createCopyBufferHandle, m_dataSize, m_dataTopPos.get());
	}
}