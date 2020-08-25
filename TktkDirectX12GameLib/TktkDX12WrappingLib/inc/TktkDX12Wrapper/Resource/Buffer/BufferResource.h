#ifndef BUFFER_RESOURCE_H_
#define BUFFER_RESOURCE_H_

#include <memory>		// std::unique_ptr
#include <dxgi1_6.h>	// swapChain
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../Includer/D3d12Includer.h"
#include "BufferResourceInitParamIncluder.h"
#include "BufferResourceNum.h"

namespace tktk
{
	// �O���錾�B
	class VertexBuffer;
	class IndexBuffer;
	class ConstantBuffer;
	class TextureBuffer;
	class DepthStencilBuffer;
	class RenderTargetBuffer;

	// �U��ނ̃o�b�t�@���\�[�X���Ǘ�����N���X
	class BufferResource
	{
	public:

		explicit BufferResource(const BufferResourceNum& initParam);
		~BufferResource();

	public: /* �o�b�t�@���ʂ̏��� */

		// �S�ẴA�b�v���[�h�p�̃o�b�t�@���폜����
		void deleteUploadBufferAll();

	public: /* ���_�o�b�t�@�̏��� */

		// ���_�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createVertexBuffer(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �w��̒��_�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateVertexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����
		void setVertexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* �C���f�b�N�X�o�b�t�@�̏��� */

		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// �w��̃C���f�b�N�X�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateIndexBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<unsigned short>& indexDataArray);

		// �R�}���h���X�g�Ɏw��̃C���f�b�N�X�o�b�t�@��o�^����
		void setIndexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* �萔�o�b�t�@�̏��� */

		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createCBuffer(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �w��̒萔�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̒萔�o�b�t�@���X�V����
		// ���A�b�v���[�h�o�b�t�@��V�K�ɍ쐬���A���̃o�b�t�@���玩�g�ɃR�s�[���閽�߂��R�}���h���X�g�ɓo�^����
		void updateCBuffer(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

	public: /* �e�N�X�`���o�b�t�@�̏��� */

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// �R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);
		
		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// �w��̃e�N�X�`���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx(unsigned int handle) const;

	public: /* �[�x�X�e���V���o�b�t�@�̏��� */

		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɐ[�x�X�e���V���r���[�����
		void createDsv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createDsSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void beginWriteDsBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void endWriteDsBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getDepthStencilSizePx(unsigned int handle) const;

	public: /* �����_�[�^�[�Q�b�g�o�b�t�@�̏��� */

		// �[�����烌���_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
		
		// �X���b�v�`�F�C�����烌���_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���Ƀ����_�[�^�[�Q�b�g�r���[�����
		void createRtv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createRtSrv(unsigned int handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		void endWriteBasicRtBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���v���Z�b�g��ԂɕύX����
		void endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�摜�̑傫�����擾���i�s�N�Z���j
		const tktkMath::Vector2& getRenderTargetSizePx(unsigned int handle) const;

	private:

		std::unique_ptr<VertexBuffer>		m_vertexBuffer;
		std::unique_ptr<IndexBuffer>		m_indexBuffer;
		std::unique_ptr<ConstantBuffer>		m_constantBuffer;
		std::unique_ptr<TextureBuffer>		m_textureBuffer;
		std::unique_ptr<DepthStencilBuffer>	m_depthStencilBuffer;
		std::unique_ptr<RenderTargetBuffer>	m_renderTargetBuffer;
	};
}
#endif // !BUFFER_RESOURCE_H_