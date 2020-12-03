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
		size_t create(const std::vector<ScissorRectInitParam>& initParamArray);

		// �w��̃V�U�[��`���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �w��̃V�U�[��`���R�}���h���X�g�ɓo�^����
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<ScissorRectData> m_scissorRectDataArray;
	};
}
#endif // !SCISSOR_RECT_H_