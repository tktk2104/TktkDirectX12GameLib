#ifndef LINE_2D_DATA_H_
#define LINE_2D_DATA_H_

#include "Line2DMaterialDrawFuncArgs.h"

namespace tktk
{
	// ���C���QD�̏����Ǘ�����N���X
	class Line2DMaterialData
	{
	public:

		Line2DMaterialData();
		~Line2DMaterialData();

		// ���[�u�R���X�g���N�^
		Line2DMaterialData(Line2DMaterialData&& other) noexcept;

	public:

		// �Q�c���C����`�悷��
		// ���O�t���[���ō�������_�o�b�t�@���폜���A�����Ń��C���`��p�̒��_�o�b�t�@�����A���̃��\�[�X�n���h����ێ����鏈���ׁ̈A��const�֐�
		void drawLine(const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		void updateCopyCbuffer(const Line2DMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		size_t m_createUploadCbufferHandle{ 0U };
		size_t m_createdVertexBufferHandle{ 0U };
	};
}

#endif // !LINE_2D_DATA_H_