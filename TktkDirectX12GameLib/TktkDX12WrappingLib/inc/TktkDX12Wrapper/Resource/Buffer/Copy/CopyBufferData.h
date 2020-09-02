#ifndef COPY_BUFFER_DATA_H_
#define COPY_BUFFER_DATA_H_

#include "../../../Includer/D3d12Includer.h"
#include "../BufferType.h"
#include "CopyBufferInitParam.h"

namespace tktk
{
	// コピーバッファを管理するクラス
	class CopyBufferData
	{
	public:

		CopyBufferData(ID3D12Device* device, const CopyBufferInitParam& initParam);
		~CopyBufferData();

		// コピー用コンストラクタ
		CopyBufferData(ID3D12Device* device, const CopyBufferData& other);

		// ムーブコンストラクタ
		CopyBufferData(CopyBufferData&& other) noexcept;

	public:

		// 引数のポインタのデータをコピーバッファにコピーする
		void updateBuffer(unsigned int bufferSize, const void* bufferDataTopPos);

		// 自身のコピー先のバッファの種類を取得する
		BufferType getTargetBufferType() const;

		// 自身のコピー先のバッファのハンドルを取得する
		unsigned int getTargetBufferHandle() const;

		// 引数のバッファに自身のバッファの内容をコピーするGPU命令を設定する
		void copyBuffer(ID3D12GraphicsCommandList* commandList, ID3D12Resource* targetBuffer) const;

	private:

		BufferType		m_targetBufferType;
		unsigned int	m_targetBufferHandle;
		unsigned int	m_copyBufferSize;
		ID3D12Resource* m_copyBuffer			{ nullptr };
	};
}

#endif // !COPY_BUFFER_DATA_H_