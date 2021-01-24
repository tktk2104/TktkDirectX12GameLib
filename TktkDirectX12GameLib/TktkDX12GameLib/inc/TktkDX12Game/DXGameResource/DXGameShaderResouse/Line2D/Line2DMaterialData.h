#ifndef LINE_2D_MATERIAL_DATA_H_
#define LINE_2D_MATERIAL_DATA_H_

namespace tktk
{
	struct Line2DMaterialDrawFuncArgs;

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

		size_t m_createUploadCbufferHandle		{ 0U };
		size_t m_createdUploadVertexBufferHandle{ 0U };
	};
}
#endif // !LINE_2D_MATERIAL_DATA_H_