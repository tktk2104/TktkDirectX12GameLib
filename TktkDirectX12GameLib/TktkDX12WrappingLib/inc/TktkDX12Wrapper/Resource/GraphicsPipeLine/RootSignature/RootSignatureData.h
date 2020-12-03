#ifndef ROOT_SIGNATURE_DATA_H_
#define ROOT_SIGNATURE_DATA_H_

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12RootSignature */
#include <d3d12.h>
#undef min
#undef max

#include "RootSignatureInitParam.h"

namespace tktk
{
	// ���[�g�V�O�l�`�����Ǘ�����N���X
	class RootSignatureData
	{
	public:

		RootSignatureData(ID3D12Device* device, const RootSignatureInitParam& initParam);
		~RootSignatureData();

		// ���[�u�R���X�g���N�^
		RootSignatureData(RootSignatureData&& other) noexcept;

	public:

		// �p�C�v���C���X�e�[�g����邽�߂ɂ���Q�b�^�[
		ID3D12RootSignature* getPtr() const;

		// ���g���R�}���h���X�g�ɓo�^����
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		ID3D12RootSignature* m_rootSignature{ nullptr };
	};
}
#endif // !ROOT_SIGNATURE_DATA_H_