#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <string>
#include <TktkContainer/HeapArray/HeapArray.h>
#include "TextureBufferData.h"

namespace tktk
{
	// 「TextureBufferData」を管理するクラス
	class TextureBuffer
	{
	public:

		TextureBuffer(unsigned int textureBufferNum);
		~TextureBuffer() = default;

	public:
		
		// コマンドリストを使わずに「TextureBufferData」のインスタンスを作る
		void cpuPriorityCreate(unsigned int id, ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// コマンドリストを使って「TextureBufferData」のインスタンスを作る
		void gpuPriorityCreate(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// 引数のファイルから画像情報をロードし、コマンドリストを使わずに「TextureBufferData」のインスタンスを作る
		void cpuPriorityLoad(unsigned int id, ID3D12Device* device, const std::string& texDataPath);

		// 引数のファイルから画像情報をロードし、コマンドリストを使って「TextureBufferData」のインスタンスを作る
		void gpuPriorityLoad(unsigned int id, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);
	
		// 指定のテクスチャバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(unsigned int id, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
		
		// 指定のテクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx(unsigned int id) const;

	private:

		tktkContainer::HeapArray<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_