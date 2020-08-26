#ifndef DX3D_BASE_OBJECTS_H_
#define DX3D_BASE_OBJECTS_H_

#include <memory>
#include <array>
#include <dxgi1_6.h> //IDXGIFactory6
#include <TktkMath/Structs/Vector3.h>
#include "../Includer/D3d12Includer.h"
#include "DX3DBaseObjectsInitParamIncluder.h"
#include "DX3DBaseObjectsFuncArgsIncluder.h"
#include "DX3DBaseObjectsInitParam.h"

namespace tktk
{
	// �O���錾�B
	class SwapChain;
	class Fence;
	class DX3DResource;

	// DirectX12�̕`����s�����߂̃��C���}�l�[�W���[
	class DX3DBaseObjects
	{
	public:

		explicit DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam);
		~DX3DBaseObjects();

	public: /* �`��J�n�A�I������ */

		// �`��J�n
		void beginDraw();

		// �`��I��
		void endDraw();

	public: /* ���\�[�X�쐬�A���[�h���� */

		// ���[�g�V�O�l�`�������A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRootSignature(const RootSignatureInitParam& initParam);

		// �p�C�v���C���X�e�[�g�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath);

		// ���_�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createVertexBuffer(unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �C���f�b�N�X�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createIndexBuffer(const std::vector<unsigned short>& indices);

		// �萔�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createCBuffer(unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �����_�[�^�[�Q�b�g�o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor);

		// �[�x�X�e���V���o�b�t�@�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createDsBuffer(const DepthStencilBufferInitParam& initParam);

		// �萔�A�e�N�X�`���̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam);

		// �����_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam);

		// �[�x�X�e���V���r���[�̃f�B�X�N���v�^�q�[�v�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g���ăe�N�X�`�������A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		unsigned int gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam);

		// �R�}���h���X�g���g�킸�Ƀe�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int cpuPriorityLoadTextureBuffer(const std::string& texDataPath);

		// �R�}���h���X�g���g���ăe�N�X�`�������[�h���A���̃��\�[�X�̃n���h����Ԃ��i��GPU���߂Ȃ̂ŁuexecuteCommandList()�v���Ă΂Ȃ��ƃ��[�h���������܂���j
		unsigned int gpuPriorityLoadTextureBuffer(const std::string& texDataPath);

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

	public: /* ���\�[�X�X�V���� */

		// �w�i�F��ݒ肷��
		void setBackGroundColor(const tktkMath::Color& backGroundColor);

		// �w��̒��_�o�b�t�@���X�V����
		void updateVertexBuffer(unsigned int id, unsigned int vertexTypeSize, unsigned int vertexDataCount, const void* vertexDataTopPos);

		// �w��̃C���f�b�N�X�o�b�t�@���X�V����
		void updateIndexBuffer(unsigned int id, const std::vector<unsigned short>& indexDataArray);

		// �w��̒萔�o�b�t�@���X�V����
		void updateCBuffer(unsigned int id, unsigned int constantBufferTypeSize, const void* constantBufferDataTopPos);

		// �w��̃����_�[�^�[�Q�b�g�r���[���w��̐F�ŃN���A����
		void clearRtv(unsigned int id, unsigned int rtvLocationIndex, const tktkMath::Color& color) const;

	public: /* ���\�[�X���擾���� */

		// �w��̃e�N�X�`���̃T�C�Y���擾����i�s�N�Z���j
		const tktkMath::Vector3& getTextureBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getDsBufferSizePx(unsigned int id) const;
		const tktkMath::Vector2& getRtBufferSizePx(unsigned int id) const;

	public: /* ���\�[�X���R�}���h���X�g�ɓo�^���鏈�� */

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��
		void setRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��́i�����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[�j�p�̃f�B�X�N���v�^�q�[�v�Q���R�}���h���X�g�ɐݒ肷��
		void setRtvAndDsv(unsigned int rtvDescriptorHeapId, unsigned int dsvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��̐[�x�X�e���V���r���[�p�̃f�B�X�N���v�^�q�[�v���R�}���h���X�g�ɐݒ肷��i�������_�[�^�[�Q�b�g�͐ݒ�ł��Ȃ��j
		void setOnlyDsv(unsigned int id) const;

		// �o�b�N�o�b�t�@�[��ݒ肷��
		void setBackBufferView() const;

		// �o�b�N�o�b�t�@�[�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setBackBufferViewAndDsv(unsigned int dsvDescriptorHeapId) const;

		// �w��̃����_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v���g�p���Ă��郌���_�[�^�[�Q�b�g�o�b�t�@�̏������݌㏈�����s��
		void unSetRtv(unsigned int rtvDescriptorHeapId, unsigned int startRtvLocationIndex, unsigned int rtvCount) const;

		// �w��̐[�x�������ݗp�̃f�B�X�N���v�^�q�[�v���g�p���Ă���[�x�o�b�t�@�̏������݌㏈�����s��
		void unSetDsv(unsigned int dsvDescriptorHeapId) const;

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɐݒ肷��
		void setViewport(unsigned int id) const;

		// �w��̃V�U�[��`���R�}���h���X�g�ɐݒ肷��
		void setScissorRect(unsigned int id) const;

		// �w��̃p�C�v���C���X�e�[�g���R�}���h���X�g�ɐݒ肷��
		void setPipeLineState(unsigned int id) const;

		// �w��̒��_�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setVertexBuffer(unsigned int id) const;

		// �w��̃C���f�b�N�X�o�b�t�@���R�}���h���X�g�ɐݒ肷��
		void setIndexBuffer(unsigned int id) const;

		// �w��̃f�B�X�N���v�^�q�[�v�̔z����R�}���h���X�g�ɐݒ肷��
		void setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const;

		// �u�����h�t�@�N�^�[��ݒ肷��
		void setBlendFactor(const std::array<float, 4>& blendFactor) const;

		// �v���~�e�B�u�g�|���W��ݒ肷��
		void setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology) const;

	public: /* �h���[�R�[���A���̑����� */

		// �C���X�^���X�`����s��
		void drawInstanced(
			unsigned int vertexCountPerInstance,
			unsigned int instanceCount,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		) const;

		// �C���f�b�N�X���g�p���ăC���X�^���X�`����s��
		void drawIndexedInstanced(
			unsigned int indexCountPerInstance,
			unsigned int instanceCount,
			unsigned int startIndexLocation,
			unsigned int baseVertexLocation,
			unsigned int startInstanceLocation
		) const;

		// �R�}���h���X�g�����s����
		void executeCommandList();

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

		ID3D12Device*					m_device				{ nullptr };
		IDXGIFactory6*					m_factory				{ nullptr };
		ID3D12CommandAllocator*			m_commandAllocator		{ nullptr };
		ID3D12GraphicsCommandList*		m_commandList			{ nullptr };
		ID3D12CommandQueue*				m_commandQueue			{ nullptr };
		std::unique_ptr<SwapChain>		m_swapChain;
		std::unique_ptr<Fence>			m_fence;
		std::unique_ptr<DX3DResource>	m_dX3DResource;
		tktkMath::Color					m_backGroundColor		{ tktkMath::Color_v::blue };
	};
}
#endif // !DX3D_BASE_OBJECTS_H_