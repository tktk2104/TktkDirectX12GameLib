#ifndef MONO_COLOR_INSTANCE_VERT_DATA_H_
#define MONO_COLOR_INSTANCE_VERT_DATA_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// �P�F���b�V���̃C���X�^���X�`��p���_�o�b�t�@�`��
	struct MonoColorInstanceVertData
	{
		tktkMath::Matrix4	worldMatrix;
		tktkMath::Color		albedoColor;
	};
}
#endif // !MONO_COLOR_INSTANCE_VERT_DATA_H_