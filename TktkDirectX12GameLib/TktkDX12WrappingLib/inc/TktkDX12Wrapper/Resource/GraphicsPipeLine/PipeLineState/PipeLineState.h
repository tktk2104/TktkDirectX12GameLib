#ifndef GRAPHICS_PIPELINE_STATE_H_
#define GRAPHICS_PIPELINE_STATE_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "PipeLineStateData.h"

namespace tktk
{
	// �uPipeLineStateData�v���Ǘ�����N���X
	class PipeLineState
	{
	public:

		explicit PipeLineState(const tktkContainer::ResourceContainerInitParam& initParam);
		~PipeLineState() = default;

	public:

		// �uPipeLineStateData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr);

		// �w��̃p�C�v���C���X�e�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �w�肵���p�C�v���C���X�e�[�g���g�p���Ă��郋�[�g�V�O�l�`���̃n���h�����擾����
		size_t getUseRootSignatureIndex(size_t handle) const;

		// �w�肵���p�C�v���C���X�e�[�g���R�}���h���X�g�ɓo�^����
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<PipeLineStateData> m_pipeLineStateDataArray;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_