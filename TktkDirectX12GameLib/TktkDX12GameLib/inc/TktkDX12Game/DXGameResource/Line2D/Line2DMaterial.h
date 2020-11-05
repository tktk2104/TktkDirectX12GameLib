#ifndef LINE_2D_H_
#define LINE_2D_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "Line2DMaterialData.h"

namespace tktk
{
	// �uLine2DMaterialData�v���Ǘ�����N���X
	class Line2DMaterial
	{
	public:

		Line2DMaterial(const ShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam);
		~Line2DMaterial() = default;

	public:

		// �Q�c���C�������A���̃��\�[�X�̃n���h����Ԃ�
		size_t create();

		// �Q�c���C�����폜����
		// �������̃n���h���ɑΉ����郊�\�[�X�����������牽�����Ȃ�
		void erase(size_t handle);

		// �w��̂Q�c���C����`�悷��
		// ���O�t���[���ō�������_�o�b�t�@���폜���A�����Ń��C���`��p�̒��_�o�b�t�@�����A���̃��\�[�X�n���h����ێ����鏈���ׁ̈A��const�֐�
		void drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// �Q�c���C���`��p�̃��[�g�V�O�l�`�������
		void createBasicDescriptorHeap() const;

		// �Q�c���C���`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �Q�c���C���`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::ResourceContainer<Line2DMaterialData> m_line2DMaterialArray;
	};
}
#endif // !LINE_2D_H_