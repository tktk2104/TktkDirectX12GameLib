#ifndef PIPELINE_STATE_DATA_H_
#define PIPELINE_STATE_DATA_H_

/* ID3D12Device, ID3D12GraphicsCommandList, ID3D12PipelineState, ID3D12RootSignature */
#include <d3d12.h>
#undef min
#undef max

#include "PipeLineStateInitParam.h"

namespace tktk
{
	// �p�C�v���C���X�e�[�g���Ǘ�����N���X
	class PipeLineStateData
	{
	public:

		PipeLineStateData(
			ID3D12Device* device,
			const PipeLineStateInitParam& initParam,
			const std::vector<char>& vsByteArray,
			const std::vector<char>& psByteArray,
			ID3D12RootSignature* rootSignaturePtr
		);
		~PipeLineStateData();

		// ���[�u�R���X�g���N�^
		PipeLineStateData(PipeLineStateData&& other) noexcept;

	public:

		// �g�p���Ă��郋�[�g�V�O�l�`����ID���擾����
		size_t getUseRootSignatureHandle() const;

		// ���g���R�}���h���X�g�ɓo�^����
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		size_t					m_rootSignatureHandle	{};
		ID3D12PipelineState*	m_pipeLineState			{ nullptr };
	};
}
#endif // !PIPELINE_STATE_DATA_H_