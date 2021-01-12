#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

/* std::unique_ptr */
#include <memory>

/* std::array */
#include <array>

/* std::vector */
#include <vector>

/* IDXGIFactory6 */
#include <dxgi1_6.h>

/* ID3D12Device, ID3D12CommandAllocator, ID3D12GraphicsCommandList, ID3D12CommandQueue */
#include <d3d12.h>
#undef min
#undef max

/* funcUseType */
#include <TktkMath/Structs/Vector3.h>
#include "DX3DBaseObjectsFuncArgsIncluder.h"
#include "DX3DBaseObjectsInitParam.h"
#include "DX3DBaseObjectsInitParamIncluder.h"
#include "PrimitiveTopology.h"

#include "TktkDX12Wrapper/Resource/Viewport/ViewportInitParam.h"
#include "TktkDX12Wrapper/Resource/ScissorRect/ScissorRectInitParam.h"

namespace tktk
{
	/* class member */
	class SwapChain;
	class Fence;
	class DX3DResource;

	// DirectX12�̕`����s�����߂̃��C���}�l�[�W���[
	class DX3DBaseObjects
	{
	public:

		explicit DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam);
		~DX3DBaseObjects();

	public: /* ���\�[�X�쐬�A���[�h���� */

		// �r���[�|�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createViewport(const std::vector<ViewportInitParam>& initParamArray);

		// �V�U�[��`�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createScissorRect(const std::vector<ScissorRectInitParam>& initParamArray);

		// ���[�g�V�O�l�`�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRootSignature(const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// �A�b�v���[�h�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createUploadBuffer(const UploadBufferInitParam& initParam);

		// �ꎞ�I�ȃA�b�v���[�h�o�b�t�@�����i���̃t���[���ł͏��ł���z��ׁ̈A�n���h���͕Ԃ��Ȃ��j
		void createTempUploadBuffer(const UploadBufferInitParam& initParam);

		// �A�b�v���[�h�o�b�t�@�̃R�s�[�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t duplicateUploadBuffer(size_t originalHandle);

		// ���_�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createVertexBuffer(const VertexDataCarrier& vertexData);

		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createIndexBuffer(const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createCBuffer(const CopySourceDataCarrier& constantBufferData);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �o�b�N�o�b�t�@�[���g���ă����_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		std::array<size_t, 2U> createBackBufferRtBuffer();

		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// �o�b�N�o�b�t�@�[�̃����_�[�^�[�Q�b�g�f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createBackBufferRtvDescriptorHeap(const std::array<size_t, 2U>& backBufferRtBufferHandles);

		// �[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// �e�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		size_t createTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �e�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		size_t loadTextureBuffer(const std::string& texDataPath);

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

	public: /* ���\�[�X�X�V���� */

		// �����̃|�C���^�̃f�[�^���w��̃A�b�v���[�h�o�b�t�@�ɃR�s�[����
		void updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData);

		// �w��̒��_�o�b�t�@���R�}���h���X�g���g�킸�ɍX�V����
		void updateVertexBuffer(size_t handle, const VertexDataCarrier& vertexData);

		// �w��̃A�b�v���[�h�o�b�t�@�̓��e��ݒ肵���o�b�t�@�ɃA�b�v���[�h����GPU���߂��s��
		void copyBuffer(size_t handle) const;

		// �w��̃����_�[�^�[�Q�b�g�r���[�����O�ɐݒ肵���N���A�J���[�ŃN���A����
		void clearRtv(size_t handle, size_t rtvLocationIndex) const;

		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		void clearDsvAll();

	public: /* ���\�[�X���擾���� */

		// ���݂̃o�b�N�o�b�t�@�[�����ʂ���C���f�b�N�X���擾����
		unsigned int getCurBackBufferIndex() const;

		// �w��̃e�N�X�`���̃T�C�Y���擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getDsBufferSizePx(size_t handle) const;
		const tktkMath::Vector2& getRtBufferSizePx(size_t handle) const;

	public: /* ���\�[�X���R�}���h���X�g�ɓo�^���鏈�� */

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��
		void setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const;

		// �w��́i�����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[�j�p�̃f�B�X�N���v�^�q�[�v�Q���R�}���h���X�g�ɐݒ肷��
		void setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const;

		// �w��̐[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��i�������_�[�^�[�Q�b�g�͐ݒ�ł��Ȃ��j
		void setOnlyDsv(size_t handle) const;

		// �o�b�N�o�b�t�@�[�r���[��ݒ肷��
		void setBackBufferView(size_t backBufferRtvDescriptorHeap) const;

		// �o�b�N�o�b�t�@�[�r���[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setBackBufferViewAndDsv(size_t backBufferRtvDescriptorHeap, size_t dsvDescriptorHeapHandle) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		void unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		void unSetDsv(size_t dsvDescriptorHeapHandle) const;

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(size_t handle) const;

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(size_t handle) const;

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(size_t handle) const;

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(size_t handle) const;

		// �R�}���h���X�g�Ɏw��̒��_�o�b�t�@��o�^����i�C���X�^���X�`��p�j
		void setVertexBuffer(size_t meshVertHandle, size_t instancingVertHandle) const;

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(size_t handle) const;

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const;

		// �u�����h�t�@�N�^�[��ݒ肷��
		void setBlendFactor(const std::array<float, 4>& blendFactor) const;

		// �v���~�e�B�u�g�|���W��ݒ肷��
		void setPrimitiveTopology(PrimitiveTopology topology) const;

	public: /* �h���[�R�[���A���̑����� */

		// �o�b�N�o�b�t�@���������ݏ�Ԃɂ���
		void beginWriteBackBuffer(size_t backBufferHandle);

		// �o�b�N�o�b�t�@��`���Ԃɂ���
		void endWriteBackBuffer(size_t backBufferHandle);

		// �C���X�^���X�`����s��
		void drawInstanced(
			size_t vertexCountPerInstance,
			size_t instanceCount,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		) const;

		// �C���f�b�N�X���g�p���ăC���X�^���X�`����s��
		void drawIndexedInstanced(
			size_t indexCountPerInstance,
			size_t instanceCount,
			size_t startIndexLocation,
			size_t baseVertexLocation,
			size_t startInstanceLocation
		) const;

		// �R�}���h���X�g�����s����
		void executeCommandList();

		// ��ʂ��t���b�v����
		void flipScreen() const;

	private:

		ID3D12Device*					m_device				{ nullptr };
		IDXGIFactory6*					m_factory				{ nullptr };
		ID3D12CommandAllocator*			m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*		m_commandList			{ nullptr };
		ID3D12CommandQueue*				m_commandQueue			{ nullptr };
		std::unique_ptr<SwapChain>		m_swapChain;
		std::unique_ptr<Fence>			m_fence;
		std::unique_ptr<DX3DResource>	m_dX3DResource;
	};
}
#endif // !DX3D_BASE_OBJECTS_H_