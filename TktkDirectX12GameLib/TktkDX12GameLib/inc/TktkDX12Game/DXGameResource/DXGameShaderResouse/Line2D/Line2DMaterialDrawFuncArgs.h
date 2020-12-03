#ifndef LINE_2D_DRAW_FUNC_ARGS_H_
#define LINE_2D_DRAW_FUNC_ARGS_H_

/* class member */
#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	// �Q�c���C���`��ɕK�v�ȕϐ�
	struct Line2DMaterialDrawFuncArgs
	{
		// �g�p����r���[�|�[�g�n���h��
		size_t		viewportHandle;

		// �g�p����V�U�[��`�n���h��
		size_t		scissorRectHandle;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�v�n���h��
		size_t		rtvDescriptorHeapHandle;

		// ���[���h�s��
		tktkMath::Matrix3	worldMatrix;

		// ���C���̐F
		tktkMath::Color		lineColor;

		// ���C�����\�����钸�_�̔z��
		std::vector<tktkMath::Vector2> lineVertexArray;
	};
}
#endif // !LINE_2D_DRAW_FUNC_ARGS_H_
