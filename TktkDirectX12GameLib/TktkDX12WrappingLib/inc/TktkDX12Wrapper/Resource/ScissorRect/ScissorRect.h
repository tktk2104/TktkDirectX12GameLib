#ifndef SCISSOR_RECT_H_
#define SCISSOR_RECT_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "ScissorRectData.h"

namespace tktk
{
	// �uScissorRectData�v���Ǘ�����N���X
	class ScissorRect
	{
	public:

		explicit ScissorRect(const tktkContainer::ResourceContainerInitParam& initParam);
		~ScissorRect() = default;

	public:

		// �uScissorRectData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(const std::vector<ScissorRectInitParam>& initParamArray);

		// �w��̃V�U�[��`���R�}���h���X�g�ɓo�^����
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<ScissorRectData> m_scissorRectDataArray;
	};
}
#endif // !SCISSOR_RECT_H_