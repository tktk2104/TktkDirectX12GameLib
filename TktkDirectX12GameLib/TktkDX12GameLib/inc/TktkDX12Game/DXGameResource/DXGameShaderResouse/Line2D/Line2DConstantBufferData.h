#ifndef LINE_2D_CONSTANT_BUFFER_DATA_H_
#define LINE_2D_CONSTANT_BUFFER_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	// �Q�c���C���`��p�̒萔�o�b�t�@
	struct Line2DConstantBufferData
	{
		// ���[���h�s��
		float				worldMatrix[12]{
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f
		};

		// ���̐F
		tktkMath::Color		lineColor;

		// ��ʃT�C�Y
		tktkMath::Vector2	screenSize;

		// �p�f�B���O
		float				pad[2]{ 0.0f, 0.0f };
	};
}
#endif // !LINE_2D_CONSTANT_BUFFER_DATA_H_