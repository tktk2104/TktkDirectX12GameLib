#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/PostEffectMaterialAppendParam.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialAppendParamInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/PostEffect/Structs/PostEffectMaterialAppendParamUpdateFuncArgs.h"

namespace tktk
{
	PostEffectMaterialAppendParam::PostEffectMaterialAppendParam(const PostEffectMaterialAppendParamInitParam& initParam)
		: m_cbufferHandle(initParam.cbufferHandle)
		, m_dataSize(initParam.dataSize)
		, m_dataTopPos(initParam.cbufferDataPtr)
	{
		// アップロード用バッファを作り、そのハンドルを取得する
		m_createUploadBufferHandle = DX12GameManager::createUploadBuffer({ BufferType::constant, m_cbufferHandle, initParam.dataSize, initParam.cbufferDataPtr.get() });
	}

	PostEffectMaterialAppendParam::~PostEffectMaterialAppendParam()
	{
		DX12GameManager::eraseUploadBuffer(m_createUploadBufferHandle);
	}

	PostEffectMaterialAppendParam::PostEffectMaterialAppendParam(PostEffectMaterialAppendParam&& other) noexcept
		: m_createUploadBufferHandle(other.m_createUploadBufferHandle)
		, m_cbufferHandle(other.m_cbufferHandle)
		, m_dataSize(other.m_dataSize)
		, m_dataTopPos(std::move(other.m_dataTopPos))
	{
		other.m_createUploadBufferHandle = 0U;
	}

	void PostEffectMaterialAppendParam::updateParam(const PostEffectMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
	{
		if (m_dataSize == updateFuncArgs.dataSize) memcpy(m_dataTopPos.get(), updateFuncArgs.dataTopPos, updateFuncArgs.dataSize);
	}

	void PostEffectMaterialAppendParam::updateCbuffer() const
	{
		// 定数バッファのコピー用バッファを更新する
		// TODO : 前フレームと定数バッファに変化がない場合、更新しない処理を作る
		updateCopyBuffer();

		// 定数バッファにコピーバッファの情報をコピーする
		DX12GameManager::copyBuffer(m_createUploadBufferHandle);
	}

	void PostEffectMaterialAppendParam::updateCopyBuffer() const
	{
		DX12GameManager::updateUploadBuffer(m_createUploadBufferHandle, CopySourceDataCarrier(m_dataSize, m_dataTopPos.get(), 0U));
	}
}