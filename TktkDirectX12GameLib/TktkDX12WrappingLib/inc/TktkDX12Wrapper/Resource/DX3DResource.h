#ifndef DX_3D_RESOURCE_H_
#define DX_3D_RESOURCE_H_

/* std::unique_ptr */
#include <memory>

/* IDXGISwapChain1 */
#include <dxgi1_6.h>

/* ID3D12Device, ID3D12GraphicsCommandList, D3D12_CPU_DESCRIPTOR_HANDLE */
#include <d3d12.h>
#undef min
#undef max

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include "DX3DResourceInitParamIncluder.h"
#include "DX3DResourceFuncArgsIncluder.h"
#include "DX3DResourceNum.h"

namespace tktk
{
	// �O���錾�B
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
		size_t createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// �V�U�[��`�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ���[�g�V�O�l�`�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRootSignature(ID3D12Device* device, const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createPipeLineState(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// �A�b�v���[�h�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createUploadBuffer(ID3D12Device* device, const UploadBufferInitParam& initParam);

		// �A�b�v���[�h�o�b�t�@�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t duplicateUploadBuffer(ID3D12Device* device, size_t originalHandle);

		// ���_�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createVertexBuffer(ID3D12Device* device, const VertexDataCarrier& vertexData);

		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createIndexBuffer(ID3D12Device* device, const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createCBuffer(ID3D12Device* device, const CopySourceDataCarrier& constantBufferData);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRtBuffer(ID3D12Device* device, const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �X���b�v�`�F�[�����烌���_�[�^�[�Q�b�g�o�b�t�@���擾���A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRtBuffer(IDXGISwapChain1* swapChain, unsigned int backBufferIndex);

		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createDsBuffer(ID3D12Device* device, const DepthStencilBufferInitParam& initParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t cpuPriorityCreateTextureBuffer(ID3D12Device* device, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		size_t gpuPriorityCreateTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h���ăo�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t cpuPriorityLoadTextureBuffer(ID3D12Device* device, const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h���ăo�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		size_t gpuPriorityLoadTextureBuffer(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::string& texDataPath);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createBasicDescriptorHeap(ID3D12Device* device, const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRtvDescriptorHeap(ID3D12Device* device, const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createDsvDescriptorHeap(ID3D12Device* device, const DsvDescriptorHeapInitParam& initParam);

	public: /* ���\�[�X�폜���� */

		// �w��̃r���[�|�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseViewport(size_t handle);

		// �w��̃V�U�[��`���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseScissorRect(size_t handle);

		// �w��̃��[�g�V�O�l�`�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRootSignature(size_t handle);

		// �w��̃p�C�v���C���X�e�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erasePipeLineState(size_t handle);

		// �w��̃A�b�v���[�h�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseUploadBuffer(size_t handle);

		// �w��̒��_�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseVertexBuffer(size_t handle);

		// �w��̃C���f�b�N�X�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseIndexBuffer(size_t handle);

		// �w��̒萔�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseCBuffer(size_t handle);

		// �w��̃e�N�X�`���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseTextureBuffer(size_t handle);

		// �w��̐[�x�X�e���V���o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseDsBuffer(size_t handle);

		// �w��̃����_�[�^�[�Q�b�g�o�b�t�@���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRtBuffer(size_t handle);

		// �w��̒ʏ�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseBasicDescriptorHeap(size_t handle);

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseRtvDescriptorHeap(size_t handle);

		// �w��̐[�x�X�e���V���p�̃f�B�X�N���v�^�q�[�v���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void eraseDsvDescriptorHeap(size_t handle);

	public: /* ���\�[�X�X�V�n���� */

		// �����̃|�C���^�̃f�[�^���w��̃A�b�v���[�h�o�b�t�@�ɃR�s�[����
		void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// �w��̒��_�o�b�t�@���R�}���h���X�g���g�킸�ɍX�V����
		void updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData);

		// �w��̃A�b�v���[�h�o�b�t�@�̓��e��ݒ肵���o�b�t�@�ɃA�b�v���[�h����GPU���߂��s��
		void copyBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃����_�[�^�[�Q�b�g�r���[�����O�ɐݒ肵���N���A�J���[�ŃN���A����
		void clearRtv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t rtvLocationIndex) const;

		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		void clearDsvAll(ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

	public: /* ���\�[�X���擾�n���� */

		// �w��̃o�b�t�@�̃e�N�X�`���Ƃ��ẴT�C�Y���擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getDsBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getRtBufferSizePx(size_t handle) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�[��ID���擾����
		const std::vector<size_t>& getRtvDescriptorHeapUseBufferHandleArray(size_t handle) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�[��ID���擾����
		const std::vector<size_t>& getDsvDescriptorHeapUseBufferHandleArray(size_t handle) const;

	public: /* �`�揀�� */

		// �����_�[�^�[�Q�b�g�r���[���R�}���h���X�g�ɐݒ肷��
		void setRtv(size_t rtvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const;

		// �����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		void setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const;

		// �[�x�X�e���V���r���[���R�}���h���X�g�ɐݒ肷��
		// �������_�[�^�[�Q�b�g�r���[�͐ݒ�ł��Ȃ�
		void setOnlyDsv(size_t handle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@�[�r���[��ݒ肷��
		void setBackBufferView(size_t backBufferRtvDescriptorHeap, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// �o�b�N�o�b�t�@�[�r���[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setBackBufferViewAndDsv(size_t backBufferRtvDescriptorHeap, size_t dsvDescriptorHeapHandle, ID3D12Device* device, ID3D12GraphicsCommandList* commandList, unsigned int backBufferIndex) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		void unSetRtv(size_t rtvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList, size_t startRtvLocationIndex, size_t rtvCount) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		void unSetDsv(size_t dsvDescriptorHeapHandle, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@�������_�[�^�[�Q�b�g��Ԃɂ���
		// TODO : �uunsigned int id�v���uunsigned int backBufferIndex�v�ɕύX����
		void beginWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �o�b�N�o�b�t�@���v���Z�b�g��Ԃɂ���
		// TODO : �uunsigned int id�v���uunsigned int backBufferIndex�v�ɕύX����
		void endWriteBackBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����i�C���X�^���X�`��p�j
		void setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(size_t handle, ID3D12GraphicsCommandList* commandList) const;

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, const std::vector<DescriptorHeapParam>& heapParamArray) const;

	private:

		// �����̃o�b�t�@��񂪒萔�o�b�t�@�ł���Β萔�o�b�t�@�r���[�����A�����łȂ���΃G���[��f��
		void createBasicDescriptorCbv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

		// �����̃o�b�t�@��񂪃V�F�[�_�[���\�[�X�ɂȂ��o�b�t�@�ł���΃V�F�[�_�[���\�[�X�r���[�����A�����łȂ���΃G���[��f��
		void createBasicDescriptorSrv(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE cpuHandle, const BasicDescriptorParam& useBufferParam) const;

	private:

		std::unique_ptr<Viewport>					m_viewport;
		std::unique_ptr<ScissorRect>				m_scissorRect;
		std::unique_ptr<GraphicsPipeLine>			m_graphicsPipeLine;
		std::unique_ptr<DescriptorHeap>				m_descriptorHeap;
		std::unique_ptr<BufferResource>				m_bufferResource;
	};
}
#endif // !DX_3D_RESOURCE_H_