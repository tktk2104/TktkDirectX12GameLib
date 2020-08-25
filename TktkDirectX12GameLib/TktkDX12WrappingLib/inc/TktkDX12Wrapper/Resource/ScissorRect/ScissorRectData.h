#ifndef SCISSOR_RECT_DATA_H_
#define SCISSOR_RECT_DATA_H_

#include <vector>
#include "../../Includer/D3d12Includer.h"
#include "ScissorRectInitParam.h"

namespace tktk
{
	// �V�U�[��`���Ǘ�����N���X
	class ScissorRectData
	{
	public:

		explicit ScissorRectData(const std::vector<ScissorRectInitParam>& initParamArray);
		~ScissorRectData() = default;

		// ���[�u�R���X�g���N�^
		ScissorRectData(ScissorRectData&& other) noexcept;

	public:

		// ���g���R�}���h���X�g�ɓo�^����
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		std::vector<D3D12_RECT> m_scissorRectArray{};
	};
}
#endif // !SCISSOR_RECT_DATA_H_