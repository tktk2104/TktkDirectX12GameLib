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
		
		// コマンドリストを使わずに「TextureBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t cpuPriorityCreate(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// コマンドリストを使って「TextureBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t gpuPriorityCreate(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// 引数のファイルから画像情報をロードし、コマンドリストを使わずに「TextureBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t cpuPriorityLoad(ID3D12Device* device, const std::string& texDataPath);

		// 引数のファイルから画像情報をロードし、コマンドリストを使って「TextureBufferData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t gpuPriorityLoad(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);
	
		// 指定のテクスチャバッファを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定のテクスチャバッファを使用して、引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;
		
		// 指定のテクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx(size_t handle) const;

		// 指定のテクスチャバッファのポインタを取得する
		ID3D12Resource* getBufferPtr(size_t handle) const;

		// 指定のテクスチャバッファのコピーに使用するフットプリント指定の設定情報構造体を作る
		D3D12_TEXTURE_COPY_LOCATION createSrcCopyLoaction(size_t handle) const;

	private:

		tktkContainer::ResourceContainer<TextureBufferData> m_textureBufferDataArray;
	};
}
#endif // !TEXTURE_BUFFER_H_