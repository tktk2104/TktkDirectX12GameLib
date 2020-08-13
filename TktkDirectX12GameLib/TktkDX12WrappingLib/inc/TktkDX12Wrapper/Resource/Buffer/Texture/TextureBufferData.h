#ifndef TEXTURE_BUFFER_DATA_H_
#define TEXTURE_BUFFER_DATA_H_

#include <d3d12.h>
#undef min
#undef max
#include <TktkMath/Structs/Vector3.h>
#include "TextureBufferInitParam.h"
#include "ShaderResourceViewInitParam.h"

namespace tktk
{
	// テクスチャバッファを管理するクラス
	class TextureBufferData
	{
	public:

		// コマンドリストを使わずに作るコンストラクタ
		TextureBufferData(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// コマンドリストを使って作るコンストラクタ
		TextureBufferData(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		~TextureBufferData();

	public:

		// 引数のディスクリプタハンドルにシェーダーリソースビューを作る
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// テクスチャバッファ画像の大きさを取得する（ピクセル）
		const tktkMath::Vector3& getTextureSizePx() const;

	private:

		tktkMath::Vector3			m_textureSize{ 1.0f, 1.0f, 1.0f };
		ShaderResourceViewInitParam	m_srvInitParam{};
		ID3D12Resource*				m_textureBuffer{ nullptr };
		ID3D12Resource*				m_uploadBuff{ nullptr };
	};
}
#endif // !TEXTURE_BUFFER_DATA_H_