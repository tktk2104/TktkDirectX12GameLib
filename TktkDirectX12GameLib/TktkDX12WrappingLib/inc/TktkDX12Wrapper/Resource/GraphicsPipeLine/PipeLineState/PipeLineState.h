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
		unsigned int create(ID3D12Device* device, const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, ID3D12RootSignature* rootSignaturePtr);

		// �w��̃p�C�v���C���X�e�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �w�肵���p�C�v���C���X�e�[�g���g�p���Ă��郋�[�g�V�O�l�`���̃n���h�����擾����
		unsigned int getUseRootSignatureIndex(unsigned int handle) const;

		// �w�肵���p�C�v���C���X�e�[�g���R�}���h���X�g�ɓo�^����
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<PipeLineStateData> m_pipeLineStateDataArray;
	};
}
#endif // !GRAPHICS_PIPELINE_STATE_H_