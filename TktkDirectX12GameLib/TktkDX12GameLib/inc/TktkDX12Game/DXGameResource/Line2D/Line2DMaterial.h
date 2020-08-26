#ifndef LINE_2D_H_
#define LINE_2D_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "Line2DMaterialData.h"

namespace tktk
{
	// �uLine2DMaterialData�v���Ǘ�����N���X
	class Line2DMaterial
	{
	public:

		Line2DMaterial(const ShaderFilePaths& shaderFilePaths, unsigned int line2DMaterialNum);
		~Line2DMaterial() = default;

	public:

		// �Q�c���C�������
		void create(unsigned int id);

		// �w��̂Q�c���C����`�悷��
		// ���O�t���[���ō�������_�o�b�t�@���폜���A�����Ń��C���`��p�̒��_�o�b�t�@�����A���̃��\�[�X�n���h����ێ����鏈���ׁ̈A��const�֐�
		void drawLine(unsigned int id, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// �Q�c���C���`��p�̃��[�g�V�O�l�`�������
		void createBasicDescriptorHeap() const;

		// �Q�c���C���`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �Q�c���C���`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::HeapArray<Line2DMaterialData> m_line2DMaterialArray;
	};
}
#endif // !LINE_2D_H_