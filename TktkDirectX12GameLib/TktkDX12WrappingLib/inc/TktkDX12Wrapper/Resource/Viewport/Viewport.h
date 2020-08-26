#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "ViewportData.h"

namespace tktk
{
	// �uViewportData�v���Ǘ�����N���X
	class Viewport
	{
	public:

		explicit Viewport(const tktkContainer::ResourceContainerInitParam& initParam);
		~Viewport() = default;

	public:

		// �uViewportData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(const std::vector<ViewportInitParam>& initParamArray);

		// �w��̃r���[�|�[�g���폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(unsigned int handle);

		// �w��̃r���[�|�[�g���R�}���h���X�g�ɓo�^����
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<ViewportData> m_viewportDataArray;
	};
}
#endif // !VIEWPORT_H_