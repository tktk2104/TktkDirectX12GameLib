#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

#include <memory>		// std::unique_ptr
#include <dxgi1_6.h>	// swapChain
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "../Includer/D3d12Includer.h"
#include "DX3DResourceInitParamIncluder.h"
#include "DX3DResourceFuncArgsIncluder.h"
#include "DX3DResourceNum.h"

namespace tktk
{
	// �O���錾�B
	class SystemResourceHandleGetter;
	class Viewport;
	class ScissorRect;
	class GraphicsPipeLine;
	class DescriptorHeap;
	class BufferResource;

	// DirectX12�̃��\�[�X���Ǘ�����N���X
	class DX3DResource
	{
	public:

		explicit DX3DResource(const DX3DResourceNum& resNum);
		~DX3DResource();

	public: /* �쐬�A���[�h���� */

		// �r���[�|�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// �V�U�[��`�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ���[�g�V�O�l�`�������A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// �R�s�[�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createCopyBuffer(ID3D12Device* device, const CopyBufferInitParam& initParam);

		// �R�s�[�o�b�t�@�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int copyCopyBuffer(ID3D12Device* device, unsigned int originalHandle);

		// ���_�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createVertexBuffer(ID3D12Device* device, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createCBuffer(ID3D12Device* device, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�[�����烌���_�[�^�[�Q�b�g�o�b�t�@���擾���A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		unsigned int gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h���ăo�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h���ăo�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		unsigned int gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* ���\�[�X�폜���� */

		// �w��̃r���[�|�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseViewport(unsigned int handle);

		// �w��̃V�U�[��`���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseScissorRect(unsigned int handle);

		// �w��̃��[�g�V�O�l�`�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRootSignature(unsigned int handle);

		// �w��̃p�C�v���C���X�e�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erasePipeLineState(unsigned int handle);

		// �w��̃R�s�[�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseCopyBuffer(unsigned int handle);

		// �w��̒��_�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseVertexBuffer(unsigned int handle);

		// �w��̃C���f�b�N�X�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseIndexBuffer(unsigned int handle);

		// �w��̒萔�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseCBuffer(unsigned int handle);

		// �w��̃e�N�X�`���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseTextureBuffer(unsigned int handle);

		// �w��̐[�x�X�e���V���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseDsBuffer(unsigned int handle);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRtBuffer(unsigned int handle);

		// �w��̒ʏ�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseBasicDescriptorHeap(unsigned int handle);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRtvDescriptorHeap(unsigned int handle);

		// �w��̐[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseDsvDescriptorHeap(unsigned int handle);

	public: /* ���\�[�X�X�V�n���� */

		// �����̃|�C���^�̃f�[�^���w��̃R�s�[�o�b�t�@�ɃR�s�[����
		void updateCopyBuffer(unsigned int handle, unsigned int bufferSize, const void* bufferDataTopPos);

		// �w��̃R�s�[�o�b�t�@�̓��e��ݒ肵���o�b�t�@�ɃR�s�[����GPU���߂�ݒ肷��
		void copyBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		void clearRtv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* ���\�[�X���擾�n���� */

		// �w��̃o�b�t�@�̃e�N�X�`���Ƃ��ẴT�C�Y���擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int handle) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int handle) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int handle) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�[��ID���擾����
		const std::vector<unsigned int>& getRtvDescriptorHeapUseBufferIdArray(unsigned int handle) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�[��ID���擾����
		const std::vector<unsigned int>& getDsvDescriptorHeapUseBufferIdArray(unsigned int handle) const;

	public: /* �`�揀�� */

		// �����_�[�^�[�Q�b�g�r���[���R�}���h���X�g�ɐݒ肷��
		void setRtv(unsigned int rtvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		void setRtvAndDsv(unsigned int rtvDescriptorHeapHandle, unsigned int dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �[�x�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		// �������_�[�^�[�Q�b�g�r���[�͐ݒ�ł��Ȃ�
		void setOnlyDsv(unsigned int handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@�[�r���[��ݒ肷��
		void setBackBufferView(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// �o�b�N�o�b�t�@�[�r���[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		void unSetRtv(unsigned int rtvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		void unSetDsv(unsigned int dsvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@�������_�[�^�[�Q�b�g��Ԃɂ���
		// TODO : �uunsigned int id�v���uunsigned int backBufferIndex�v�ɕύX����
		void beginWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@���v���Z�b�g��Ԃɂ���
		// TODO : �uunsigned int id�v���uunsigned int backBufferIndex�v�ɕύX����
		void endWriteBackBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	public: /* �V�X�e���̃��\�[�X���g�����߂̃n���h�����擾���� */

		// �V�X�e���̃r���[�|�[�g�n���h�����擾����
		unsigned int getSystemHandle(SystemViewportType type) const;

		// �V�X�e���̃V�U�[��`�n���h�����擾����
		unsigned int getSystemHandle(SystemScissorRectType type) const;

		// �V�X�e���̒��_�o�b�t�@�n���h�����擾����
		unsigned int getSystemHandle(SystemVertexBufferType type) const;

		// �V�X�e���̃C���f�b�N�X�o�b�t�@�n���h�����擾����
		unsigned int getSystemHandle(SystemIndexBufferType type) const;

		// �V�X�e���̒萔�o�b�t�@�n���h�����擾����
		unsigned int getSystemHandle(SystemCBufferType type) const;

		// �V�X�e���̃e�N�X�`���o�b�t�@�n���h�����擾����
		unsigned int getSystemHandle(SystemTextureBufferType type) const;

		// �V�X�e���̃����_�[�^�[�Q�b�g�o�b�t�@�n���h�����擾����
		unsigned int getSystemHandle(SystemRtBufferType type) const;

		// �V�X�e���̐[�x�X�e���V���o�b�t�@�n���h�����擾����
		unsigned int getSystemHandle(SystemDsBufferType type) const;

		// �V�X�e���̒ʏ�̃f�B�X�N���v�^�q�[�v�n���h�����擾����
		unsigned int getSystemHandle(SystemBasicDescriptorHeapType type) const;

		// �V�X�e���̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�n���h�����擾����
		unsigned int getSystemHandle(SystemRtvDescriptorHeapType type) const;

		// �V�X�e���̐[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v�n���h�����擾����
		unsigned int getSystemHandle(SystemDsvDescriptorHeapType type) const;

		// �V�X�e���̃��[�g�V�O�l�`���n���h�����擾����
		unsigned int getSystemHandle(SystemRootSignatureType type) const;

		// �V�X�e���̃p�C�v���C���X�e�[�g�n���h�����擾����
		unsigned int getSystemHandle(SystemPipeLineStateType type) const;

	public: /* �V�X�e���̃��\�[�X���g�����߂̃n���h���ƃV�X�e���̃��\�[�X�̎�ނ����т��� */

		void setSystemHandle(SystemViewportType type,				unsigned int handle);
		void setSystemHandle(SystemScissorRectType type,			unsigned int handle);
		void setSystemHandle(SystemVertexBufferType type,			unsigned int handle);
		void setSystemHandle(SystemIndexBufferType type,			unsigned int handle);
		void setSystemHandle(SystemCBufferType type,				unsigned int handle);
		void setSystemHandle(SystemTextureBufferType type,			unsigned int handle);
		void setSystemHandle(SystemRtBufferType type,				unsigned int handle);
		void setSystemHandle(SystemDsBufferType type,				unsigned int handle);
		void setSystemHandle(SystemBasicDescriptorHeapType type,	unsigned int handle);
		void setSystemHandle(SystemRtvDescriptorHeapType type,		unsigned int handle);
		void setSystemHandle(SystemDsvDescriptorHeapType type,		unsigned int handle);
		void setSystemHandle(SystemRootSignatureType type,			unsigned int handle);
		void setSystemHandle(SystemPipeLineStateType type,			unsigned int handle);

	private:

		// �����̃o�b�t�@��񂪒萔�o�b�t�@�ł���Β萔�o�b�t�@�r���[�����A�����łȂ���΃G���[��f��
		void createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

		// �����̃o�b�t�@��񂪃V�F�[�_�[���\�[�X�ɂȂ��o�b�t�@�ł���΃V�F�[�_�[���\�[�X�r���[�����A�����łȂ���΃G���[��f��
		void createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

	private:

		std::unique_ptr<SystemResourceHandleGetter>	m_sysResHandleGetter;
		std::unique_ptr<Viewport>					m_viewport;
		std::unique_ptr<ScissorRect>				m_scissorRect;
		std::unique_ptr<GraphicsPipeLine>			m_graphicsPipeLine;
		std::unique_ptr<DescriptorHeap>				m_descriptorHeap;
		std::unique_ptr<BufferResource>				m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_