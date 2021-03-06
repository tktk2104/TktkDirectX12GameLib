#ifndef TEXTURE_BUFFER_DATA_H_
#define TEXTURE_BUFFER_DATA_H_

/* DXGI_FORMAT, D3D12_SRV_DIMENSION, ID3D12Device, ID3D12GraphicsCommandList, D3D12_CPU_DESCRIPTOR_HANDLE, ID3D12Resource */
#include <d3d12.h>
#undef min
#undef max

#include <TktkMath/Structs/Vector3.h>
#include "TextureBufferInitParam.h"

namespace tktk
{
	// テクスチャバッファを管理するクラス
	class TextureBufferData
	{
	private:

		struct SrvInitParam
		{
			DXGI_FORMAT			format{};
			D3D12_SRV_DIMENSION viewDimension{};
			unsigned int		mostDetailedMip{};
			unsigned int		mipLevels{};
			unsigned int		firstArraySlice{};
			unsigned int		arraySize{};
			unsigned int		planeSlice{};
			float				minLodClamp{};
		};

	public:

		// コマンドリストを使わずに作るコンストラクタ
		TextureBufferData(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使って作るコンストラクタ
		TextureBufferData(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		~TextureBufferData();

		// ムーブコンストラクタ
		TextureBufferData(TextureBufferData&& other) noexcept;

	public:

		// 引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// テクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx() const;

		// 自身のバッファのポインタを取得する
		ID3D12Resource* getBufferPtr() const;

		// テクスチャバッファのコピーに使用するフットプリント指定の設定情報構造体を作る
		D3D12_TEXTURE_COPY_LOCATION createSrcCopyLoaction() const;

	private:

		tktkMath::Vector3	m_textureSize	{ 1.0f, 1.0f, 1.0f };
		SrvInitParam		m_srvInitParam	{};
		ID3D12Resource*		m_textureBuffer	{ nullptr };
		ID3D12Resource*		m_uploadBuff	{ nullptr };
	};
}
#endif // !TEXTURE_BUFFER_DATA_H_