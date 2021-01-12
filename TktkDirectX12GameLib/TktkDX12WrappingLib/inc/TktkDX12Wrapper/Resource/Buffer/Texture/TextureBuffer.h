#ifndef TEXTURE_BUFFER_H_
#define TEXTURE_BUFFER_H_

#include <string>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "TextureBufferData.h"

namespace tktk
{
	// 「TextureBufferData」を管理するクラス
	class TextureBuffer
	{
	public:

		explicit TextureBuffer(const tktkContainer::ResourceContainerInitParam& initParam);
		~TextureBuffer() = default;

	public:
		
		// 「TextureBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// 指定のテクスチャバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定のテクスチャバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
		
		// 指定のテクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx(size_t handle) const;

		// 指定のテクスチャバッファのポインタを取得する
		ID3D12Resource* getBufferPtr(size_t handle) const;

		// 指定のテクスチャバッファの１ピクセルのデータのバイトサイズを取得する
		size_t getPixDataSizeByte(size_t handle) const;

		// 指定のテクスチャバッファのコピーに使用するフットプリント指定の設定情報構造体を作る
		D3D12_TEXTURE_COPY_LOCATION createSrcCopyLoaction(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_