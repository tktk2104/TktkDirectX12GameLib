#ifndef ROOT_SIGNATURE_H_
#define ROOT_SIGNATURE_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "RootSignatureData.h"

namespace tktk
{
	// �uRootSignatureData�v���Ǘ�����N���X
	class RootSignature
	{
	public:

		explicit RootSignature(const tktkContainer::ResourceContainerInitParam& initParam);
		~RootSignature() = default;

	public:

		// �uRootSignatureData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(ID3D12Device* device, const RootSignatureInitParam& initParam);

		// �w��̃��[�g�V�O�l�`�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �w�肵�����[�g�V�O�l�`���̃|�C���^���擾����
		ID3D12RootSignature* getPtr(unsigned int handle) const;

		// �w�肵�����[�g�V�O�l�`�����R�}���h���X�g�ɓo�^����
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<RootSignatureData> m_rootSignatureDataArray;
	};
}
#endif // !ROOT_SIGNATURE_H_