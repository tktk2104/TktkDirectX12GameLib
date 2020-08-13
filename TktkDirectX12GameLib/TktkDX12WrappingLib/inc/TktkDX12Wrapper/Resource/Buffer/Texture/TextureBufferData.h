#ifndef TEXTURE_BUFFER_DATA_H_
#define TEXTURE_BUFFER_DATA_H_

#include <TktkMath/Structs/Vector3.h>
#include "../../../Includer/D3d12Includer.h"
#include "TextureBufferInitParam.h"

namespace tktk
{
	// �e�N�X�`���o�b�t�@���Ǘ�����N���X
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

		// �R�}���h���X�g���g�킸�ɍ��R���X�g���N�^
		TextureBufferData(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���č��R���X�g���N�^
		TextureBufferData(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		~TextureBufferData();

	public:

		// �����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx() const;

	private:

		tktkMath::Vector3	m_textureSize{ 1.0f, 1.0f, 1.0f };
		SrvInitParam		m_srvInitParam{};
		ID3D12Resource*		m_textureBuffer{ nullptr };
		ID3D12Resource*		m_uploadBuff{ nullptr };
	};
}
#endif // !TEXTURE_BUFFER_DATA_H_