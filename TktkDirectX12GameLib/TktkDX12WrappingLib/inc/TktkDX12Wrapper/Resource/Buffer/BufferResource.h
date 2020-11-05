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
	class UploadBuffer;
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

	public: /* �A�b�v���[�h�o�b�t�@�̏��� */

		// �A�b�v���[�h�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createUploadBuffer(ID3D12Device* device, const UploadBufferInitParam& initParam);

		// �A�b�v���[�h�o�b�t�@�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t duplicateUploadBuffer(ID3D12Device* device, size_t originalHandle);

		// �w��̃A�b�v���[�h�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseUploadBuffer(size_t handle);

		// �����̃|�C���^�̃f�[�^���w��̃A�b�v���[�h�o�b�t�@�ɃR�s�[����
		void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// �w��̃A�b�v���[�h�o�b�t�@�̓��e��ݒ肵���o�b�t�@�ɃA�b�v���[�h����GPU���߂�ݒ肷��
		void copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* ���_�o�b�t�@�̏��� */

		// ���_�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createVertexBuffer(ID3D12Device* device, const VertexDataCarrier& vertexData);

		// �w��̒��_�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseVertexBuffer(size_t handle);

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����
		void setVertexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* �C���f�b�N�X�o�b�t�@�̏��� */

		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indexDataArray);

		// �w��̃C���f�b�N�X�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseIndexBuffer(size_t handle);

		// �R�}���h���X�g�Ɏw��̃C���f�b�N�X�o�b�t�@��o�^����
		void setIndexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	public: /* �萔�o�b�t�@�̏��� */

		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createCBuffer(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData);

		// �w��̒萔�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseCBuffer(size_t handle);

		// �w��̒萔�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɒ萔�o�b�t�@�r���[�����
		void createCbv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

	public: /* �e�N�X�`���o�b�t�@�̏��� */

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);
		
		// �R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);
		
		// �����̃t�@�C������摜�������[�h���A�R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// �w��̃e�N�X�`���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseTextureBuffer(size_t handle);

		// �w��̃e�N�X�`���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃e�N�X�`���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureSizePx(size_t handle) const;

	public: /* �[�x�X�e���V���o�b�t�@�̏��� */

		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �w��̐[�x�X�e���V���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseDsBuffer(size_t handle);

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɐ[�x�X�e���V���r���[�����
		void createDsv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createDsSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void beginWriteDsBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void endWriteDsBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A��[�x�������ݏ�ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allBeginWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// �S�Ă̐[�x�X�e���V���o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		// ���V�F�[�_�[���\�[�X�Ƃ��Ďg�p���Ȃ��ݒ�̏ꍇ�ǂ�ł������N���Ȃ�
		void allEndWriteDsBuffer(ID3D12GraphicsCommandList* commandList) const;

		// �w��̐[�x�X�e���V���o�b�t�@�摜�̑傫�����擾����i�s�N�Z���j
		const tktkMath::Vector2& getDepthStencilSizePx(size_t handle) const;

	public: /* �����_�[�^�[�Q�b�g�o�b�t�@�̏��� */

		// �[�����烌���_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);
		
		// �X���b�v�`�F�C�����烌���_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRtBuffer(size_t handle);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���Ƀ����_�[�^�[�Q�b�g�r���[�����
		void createRtv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���g�p���āA�����̃f�B�X�N���v�^�n���h���ɃV�F�[�_�[���\�[�X�r���[�����
		void createRtSrv(size_t handle, ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE heapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���V�F�[�_�[�g�p��ԂɕύX����
		void endWriteBasicRtBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A�������_�[�^�[�Q�b�g��ԂɕύX����
		void beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�̃��\�[�X�o���A���v���Z�b�g��ԂɕύX����
		void endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@�摜�̑傫�����擾���i�s�N�Z���j
		const tktkMath::Vector2& getRenderTargetSizePx(size_t handle) const;

	private:

		std::unique_ptr<UploadBuffer>		m_uploadBuffer;
		std::unique_ptr<VertexBuffer>		m_vertexBuffer;
		std::unique_ptr<IndexBuffer>		m_indexBuffer;
		std::unique_ptr<ConstantBuffer>		m_constantBuffer;
		std::unique_ptr<TextureBuffer>		m_textureBuffer;
		std::unique_ptr<DepthStencilBuffer>	m_depthStencilBuffer;
		std::unique_ptr<RenderTargetBuffer>	m_renderTargetBuffer;
	};
}
#endif // !BUFFER_RESOURCE_H_